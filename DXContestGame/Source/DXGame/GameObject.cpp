#include <DXGame/GameObject.h>
#include <DXGame/Component.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/Scene.h>


// コンストラクタ
GameObject::GameObject(SceneBase* scene, const Transform& transform)
    : m_isActive(true)
    , m_isCreatePrefab(false)
    , m_name(DEFAULT_NAME_GAMEOBJECT)
    , m_transform(transform)
    , m_oldTransform(transform)
    , m_scene(scene) {
}
// デストラクタ
GameObject::~GameObject(void) {
}


// コンポーネントの初期化処理を行う
void GameObject::Start(void) {
    //----- 初期化処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() == false) {   // 初期化が行われていなければアクティブ関係なしに初期化処理を行う
            it->GameObjectStart();
        }
    }
}
// コンポーネントの更新処理を行う
void GameObject::Update(void) {
    //----- ゲームオブジェクト自身が有効でなければ処理自体をスキップする
    if (m_isActive == false) return;

    //----- 更新処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // アクティブかつ初期化が行われていれば更新処理を行う
            it->Update();
        }
    }
}
// コンポーネントの後更新処理を行う
void GameObject::LateUpdate(void) {
    //----- ゲームオブジェクト自身が有効でなければ処理自体をスキップする
    if (m_isActive == false) return;

    //----- 後更新処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // アクティブかつ初期化が行われていれば後更新処理を行う
            it->LateUpdate();
        }
    }

    //----- 過去座標の更新
    m_oldTransform = m_transform;
}
// コンポーネントの描画処理を行う
void GameObject::Draw(void) {
    //----- ゲームオブジェクト自身が有効でなければ処理自体をスキップする
    if (m_isActive == false) return;

    //----- 描画処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // アクティブかつ初期化が行われていれば描画処理を行う
            it->Draw();
        }
    }
}
// コンポーネントの当たり判定処理を行う
void GameObject::CollsionUpdate(void) {
    //----- ゲームオブジェクト自身が有効でなければ処理自体をスキップする
    if (m_isActive == false) return;

    //----- 描画処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // アクティブかつ初期化が行われていれば描画処理を行う
            it->Collsion();
        }
    }
}


// プレハブを生成する
const bool GameObject::CreatePrefab(void) {
    //----- 生成する
    if (m_isCreatePrefab == false) {
        //----- 生成されていない。プレハブ生成を行う
        m_isCreatePrefab = true;
        Prefab();
        return true;
    }

    //----- 既に生成されている
    return false;
}


// ゲームオブジェクト消去
void GameObject::DeleteGameObject(void) {
    m_scene->GetUpdater()->DeleteGameObject(this);
}


// コンポーネントを追加する
Component* GameObject::AddComponent(Component* component)
{
    m_component.push_back(std::unique_ptr<Component>(component));
    return m_component.back().get();
}
// 当たり判定を追加する
Collsion* GameObject::AddCollsion(const bool isHitMove, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& pos) {
    m_collsion.push_back(std::unique_ptr<Collsion>(new Collsion(this, isHitMove, size, pos)));
    return m_collsion.back().get();
}


// 当たり判定を取る
void GameObject::UpdateCollsion(GameObject* const gameObject) {
    //----- 自身と対象のCollsionで当たり判定を取る
    for (auto& it : m_collsion) {
        for (auto& targetIt : gameObject->m_collsion) {
            //----- 当たり判定をとる
            auto next = it->CollsionHitCheck(targetIt.get());

            //----- さらにベクトルを使った当たり判定を行うか（高速移動に対応した当たり判定）
        }
    }
}
// 当たり判定が存在するか
const bool GameObject::GetCollsionEnable(void) const {
    return m_collsion.empty();
}
// 当たり判定リストの消去
void GameObject::ResetCollsionData(void) {
    m_collsionData.list.clear();
}
