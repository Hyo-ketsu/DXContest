#ifndef ____GAMEOBJECT_H____
#define ____GAMEOBJECT_H____

#include <DXGame/ClassName.h>
#include <DXGame/Transform.h>
#include <DXGame/Component.h>
#include <DXGame/Collsion.h>


// ゲームオブジェクト
class GameObject {
public:
    // コンストラクタ
    // @ Arg1 : 所属シーン
    // @ Arg2 : 座標（デフォルト：座標回転は 0,拡縮は 1）
    GameObject(SceneBase* scene, const Transform& transform = Transform());
    // デストラクタ
    virtual ~GameObject(void);


    // アクティブゲッター
    const bool GetActive(void) const { return m_isActive; }
    // アクティブセッター
    void SetActive(const bool in) { m_isActive = in; }


    // 名前ゲッター
    const std::string& GetName(void) const { return m_name; }
    // 名前セッター
    void SetName(const std::string& in) { m_name = in; }


    // 座標ゲッター
    const Transform& GetTransform(void) const { return m_transform; }
    // 座標セッター
    void SetTransform(const Transform in) { m_transform = in; }


    // 旧座標ゲッター
    const Transform& GetOldTransform(void) const { return m_oldTransform; }


    // 当たり判定リストゲッター
    const CollsionHitDataVector& GetCollsionData(void) const { return m_collsionData; }
    // 当たり判定リストゲッター
    CollsionHitDataVector* const GetCollsionDataPointer(void) { return &m_collsionData; }
    // 当たり判定リストセッター
    void SetCollsionData(const CollsionHitDataVector& in) { m_collsionData = in; }


    // プレハブ生成可否ゲッター
    const bool GetCreatePrefab(void) const { return m_isCreatePrefab; }


    // シーンゲッター
    SceneBase* const GetScene(void) const { return m_scene; }


    // コンポーネントの初期化処理を行う
    // @ Memo : 他ゲーム処理(Update等)と違いアクティブ如何によらず初期化処理を行います
    void Start(void);
    // コンポーネントの更新処理を行う
    // @ Memo : アクティブステータスによってゲームオブジェクト単位・コンポーネント単位で行うか決定されます
    void Update(void);
    // コンポーネントの後更新処理を行う
    // @ Memo : アクティブステータスによってゲームオブジェクト単位・コンポーネント単位で行うか決定されます
    void LateUpdate(void);
    // コンポーネントの描画処理を行う
    // @ Memo : アクティブステータスによってゲームオブジェクト単位・コンポーネント単位で行うか決定されます
    void Draw(void);
    // コンポーネントの当たり判定処理を行う
    // @ Memo : アクティブステータスによってゲームオブジェクト単位・コンポーネント単位で行うか決定されます
    void CollsionUpdate(void);


    // プレハブを生成する
    // @ Ret  : 生成したか（未生成であれば true,生成済みであれば false）
    const bool CreatePrefab(void);


    // ゲームオブジェクト消去
    void DeleteGameObject(void);


    // コンポーネントを追加する
    // @ Ret  : 追加したコンポーネント
    // @ Arg1 : 追加するコンポーネント
    Component* AddComponent(Component* component);
    // コンポーネントを追加する
    // @ Ret  : 追加したコンポーネント
    // @ Temp : 追加するコンポーネントの型
    template <typename TComponent>
    TComponent* AddComponent(void);
    // 当たり判定を追加する
    // @ Ret  : 追加した当たり判定
    // @ Arg1 : 引き戻しを行うか
    // @ Arg2 : 拡縮（デフォルト：全て1）
    // @ Arg3 : 相対座標（デフォルト：全て0）
    Collsion* AddCollsion(const bool isHitMove, const DirectX::XMFLOAT3& size = DirectX::XMFLOAT3(1, 1, 1), const DirectX::XMFLOAT3& pos = DirectX::XMFLOAT3(0, 0, 0));


    // コンポーネントを取得する
    // @ Temp : 取得するコンポーネントの型
    template <typename TComponent>
    TComponent* GetComponent(void);


    // 当たり判定を取る
    // @ Arg1 : 当たり判定を取る対象のゲームオブジェクト
    void UpdateCollsion(GameObject* const gameObject);
    // 当たり判定が存在するか
    // @ Ret  : 存在するか
    const bool GetCollsionEnable(void) const;
    // 当たり判定リストの消去
    void ResetCollsionData(void);

protected:
    // プレハブを生成する
    virtual void Prefab(void) {}

private:
    bool m_isActive;            // 現在有効になっているか
    bool m_isCreatePrefab;      // プレハブが生成されたか
    std::string m_name;         // 名前
    Transform   m_transform;    // 座標
    Transform   m_oldTransform; // 前フレーム座標
    SceneBase*  m_scene;        // 所属シーン
    std::vector<std::unique_ptr<Component>> m_component;    // 保持コンポーネント
    std::vector<std::unique_ptr<Collsion>>  m_collsion;     // 保持当たり判定
    CollsionHitDataVector                   m_collsionData; // 当たり判定情報の保持
};


// コンポーネントを追加する
// @ Temp : 追加するコンポーネントの型
template <typename TComponent>
TComponent* GameObject::AddComponent(void) {
    //----- Templateがコンポーネントを継承していなかったらアソート
    static_assert(std::is_base_of_v<Component, TComponent>, "Template error! Not a class that inherits Component!");

    //----- 追加
    m_component.push_back(std::unique_ptr<TComponent>(new TComponent(this)));

    //----- 返却
    return dynamic_cast<TComponent*>(m_component.back().get());
}


// コンポーネントを取得する
// @ Temp : 取得するコンポーネントの型
template <typename TComponent>
TComponent* GameObject::GetComponent(void) {
    //----- Templateがコンポーネントを継承していなかったらアソート
    static_assert(std::is_base_of_v<Component, TComponent>, "Template error! Not a class that inherits Component!");

    //----- 取得
    for (auto& it : m_component) {
        //----- ダウンキャストできるか
        if (dynamic_cast<TComponent*>(it.get()) != nullptr) {
            //----- 可能。指定された型として返却する
            return dynamic_cast<TComponent*>(it.get());
        }
    }

    //----- 存在しない。nullptrを返す
    return nullptr;
}

#endif // !____GAMEOBJECT_H____
