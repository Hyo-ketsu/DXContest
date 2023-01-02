#include <DXGame/GameObject.h>
#include <DXGame/Component.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/SceneLoader.h>


// コンストラクタ
GameObject::GameObject(void)
    : m_isActive(true)
    , m_isCreatePrefab(false)
    , m_name(DEFAULT_NAME_GAMEOBJECT) {
    SceneLoader::Get()->GetGameUpdaterRef().AddGameObject(this);
}
// デストラクタ
GameObject::~GameObject(void) {
    SceneLoader::Get()->GetGameUpdaterRef().DeleteGameObject(this);
}


// コンポーネントの初期化処理を行う
void GameObject::Start(void) {
    //----- 初期化処理をすべてのコンポーネントに行う
    for (auto& it : m_component) {
        if (it->GetInit() == false) {   // 初期化が行われていなければアクティブ関係なしに初期化処理を行う
            it->Start();
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
            it->LateUpdate();
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


// コンポーネントを追加する
void GameObject::AddComponent(Component* component)
{
    m_component.push_back(std::unique_ptr<Component>(component));
}
