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
void GameObject::AddComponent(Component* component)
{
    m_component.push_back(std::unique_ptr<Component>(component));
}
