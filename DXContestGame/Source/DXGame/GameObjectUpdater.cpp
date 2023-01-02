#include <DXGame/GameObjectUpdater.h>
#include <DXGame/SystemDefines.h>


// コンストラクタ
GameUpdater::GameUpdater(void) { 
    m_gameObject.resize(256);   // 取り敢えず256確保する
}
// デストラクタ
GameUpdater::~GameUpdater(void) { 
}


// 更新処理を行う
void GameUpdater::Update(void) { 
    //----- 初期化処理を行う
    for (auto& it : m_gameObject) {
        it->Start();
    }

    //----- 更新処理を行う
    for (auto& it : m_gameObject) {
        it->Update();
    }

    //----- 後更新処理を行う
    for (auto& it : m_gameObject) {
        it->LateUpdate();
    }
}
// 描画処理を行う
void GameUpdater::Draw(void) { 
    //----- 描画処理を行う
    for (auto& it : m_gameObject) {
        it->Draw();
    }
}


// ゲームオブジェクトを追加する
void GameUpdater::AddGameObject(GameObject* gameObject) { 
    m_gameObject.push_back(std::unique_ptr<std::remove_reference<decltype(*m_gameObject.front().get())>::type>(gameObject));
}
// ゲームオブジェクトを削除する
const bool GameUpdater::DeleteGameObject(GameObject* gameObject) {
    //----- 検索
    for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++) {
        if (it->get() == gameObject) {
            //----- 同じゲームオブジェクト。消去
            m_gameObject.erase(it);
            return true;
        }
    }

    //----- 存在しないため消去失敗
    return false;
}


// ゲームオブジェクトを名前検索する
GameObject* GameUpdater::FindGameObject(const std::string& name) const {
    //----- デフォルトネームであれば検索自体かけない
    if (name == DEFAULT_NAME_GAMEOBJECT) return nullptr;

    //----- 検索
    for (auto& it : m_gameObject) {
        if (it->GetName() == name) {
            //----- 同じゲームオブジェクト名。返却
            return &*it;
        }
    }

    //----- 同名ゲームオブジェクトが存在しない
    return nullptr;
}
