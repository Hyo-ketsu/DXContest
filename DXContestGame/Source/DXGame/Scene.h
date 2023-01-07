#ifndef ____SCENE_H____
#define ____SCENE_H____

#include <DXGame/ClassName.h>
#include <DXGame/GameObject.h>
#include <DXGame/Transform.h>
#include <DXGame/GameObjectUpdater.h>


// シーンを作る際の抽象クラス
class SceneBase {
public:
    // コンストラクタ
    SceneBase(void);
    // デストラクタ
    ~SceneBase(void);


    // ゲームアップデーターゲッター
    GameUpdater *const GetUpdater(void) const { return m_updater.get(); }


    // シーンを生成する
    virtual void InitScene(void) = 0;


    // プレハブを生成する
    // @ Temp : 生成するゲームオブジェクトの型
    // @ Arg1 : 座標情報
    template <typename TGameObject>
    TGameObject* CreatePrefab(const Transform& transform = Transform());

private:
    std::unique_ptr<GameUpdater> m_updater; // ゲームアップデーター
};


// プレハブを生成する
// @ Temp : 生成するゲームオブジェクトの型
// @ Arg1 : 座標情報
template <typename TGameObject>
TGameObject* SceneBase::CreatePrefab(const Transform& transform) {
    //----- アソート
    // Memo : ゲームオブジェクトを継承していない（ = プレハブでない）かつ、ゲームオブジェクトでなければアソートします
    static_assert(std::disjunction_v<std::is_base_of<GameObject, TGameObject>, std::is_same<GameObject, TGameObject>>,
        "Template Error! Not a prefab or GameObject");

    //----- 生成
    TGameObject* gameObject = new TGameObject(this, transform);

    //----- 登録
    this->GetUpdater()->AddGameObject(gameObject);

    //----- 返却
    return gameObject;
}


#endif // !____SCENE_H____
