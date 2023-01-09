#include <DXGame/GameObjectUpdater.h>
#include <DXGame/SystemDefines.h>


// コンストラクタ
GameUpdater::GameUpdater(void) { 
    //m_gameObject.reserve(1024);   // 取り敢えず512確保する
}
// デストラクタ
GameUpdater::~GameUpdater(void) { 
    for (auto& it : m_gameObject) {
        if (it == nullptr) continue;
        it->DeleteGameObject();
    }
}


// 更新処理を行う
void GameUpdater::Update(void) {
    //----- 削除確認
    DeleteGameObject();

    //----- 初期化処理を行う
    for (auto& it : m_gameObject) {
        it->Start();
    }

    //----- 削除確認
    DeleteGameObject();

    //----- 更新処理を行う
    for (auto& it : m_gameObject) {
        it->Update();
    }

    //----- 削除確認
    DeleteGameObject();

    //----- 後更新処理を行う
    for (auto& it : m_gameObject) {
        it->LateUpdate();
    }

    //----- 削除確認
    DeleteGameObject();
    
    //----- 当たり判定を取る
    for (auto& it : m_gameObject) {
        if (it->GetCollsionEnable()) continue;
        it->ResetCollsionData();
        for (auto& targetIt : m_gameObject) {
            if (targetIt->GetCollsionEnable()) continue;
            it->UpdateCollsion(&*targetIt);
        }
    }

    //----- 当たり判定処理
    for (auto& it : m_gameObject) {
        it->CollsionUpdate();
    }

    //----- 削除確認
    DeleteGameObject();
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
    gameObject->CreatePrefab();
}
// ゲームオブジェクトを削除する
const bool GameUpdater::DeleteGameObject(GameObject* gameObject) {
    //----- 検索
    for (int i = 0; i < m_gameObject.size(); i++) {
        if (m_gameObject[i].get() == gameObject) {
            //----- 同ゲームオブジェクト。消去
            gameObject->SetActive(false);
            m_deleteIndex.push_back(i);
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


// 削除インデックスに登録されているゲームオブジェクトの消去
void GameUpdater::DeleteGameObject(void) {
    //----- 削除オブジェクトがあるか
    if (m_deleteIndex.empty()) return;

    //----- 変数宣言
    std::list<unsigned int> deleteIndex; // 降順にソートされ重複の排除された削除インデックス

    //----- 先頭データ挿入
    deleteIndex.push_back(m_deleteIndex.front());

    //----- 削除インデックスソート
    // Memo : 所謂挿入ソートを行っています
    // Memo : 降順にソートを行います
    // Memo : 重複を排除します
    for (auto index : m_deleteIndex) {
        //----- 要素との比較
        for (auto it = deleteIndex.begin();; it++) { // 条件式は次のif文にて
            //----- 現在値が終端（どの値より小さい）なら末尾に追加。次の入力値の比較に移る
            if (it == deleteIndex.end()) {
                deleteIndex.push_back(index);   // 末尾に追加
                break;  // 挿入、値との比較をやめ、次の入力値の比較に移る
            }

            //----- 入力値が現在値より大きい場合は挿入
            if (index > *it) {
                deleteIndex.insert(it, index);
                break;  // 挿入、値との比較をやめ、次の入力値の比較に移る
            }

            //----- 入力値が現在値と等価なら比較をやめる（＝挿入しない）
            if (index == *it) {
                break;  // 値との比較をやめ、次の入力値の比較に移る
            }
        }
    }

    //----- ゲームオブジェクト削除
    for (auto index : deleteIndex) {
        m_gameObject[index].reset();
        m_gameObject.erase(m_gameObject.begin() + index);
    }
    m_deleteIndex.clear();
}
