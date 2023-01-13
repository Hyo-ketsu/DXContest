#include <DXGame/MenuButtonSelector.h>
#include <DXGame/SpriteComponent.h>
#include <DXGame/GameDefine.h>
#include <DXGame/Input.h>
#include <DXGame/SceneLoader.h>


void MenuGameObjectClient::Start(void) {
    //----- メニューシステムに自動的に追加する
    SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_MENU)->GetComponent<MenuGameObjectControl>()->AddGameObject(m_gameObject);
}


void MenuGameObjectControl::Start(void) {
    m_currentCursor = 0;
}
void MenuGameObjectControl::Update(void) {
    //----- 座標設定
    if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
        //----- 範囲外。何もしない
    }
    else {
        //----- 範囲内。指定インデックスの
    }

    //----- 上下選択
    if (IsKeyTrigger('W') || IsKeyTrigger(VK_UP)) {
        if (m_currentCursor > 0) {
            m_gameObject->SetTransform(m_children[m_currentCursor]->GetTransform());
            m_currentCursor--;
        } 
    }
    if (IsKeyTrigger('S') || IsKeyTrigger(VK_DOWN)) {
        if (m_currentCursor < m_children.size() - 1) {
            m_gameObject->SetTransform(m_children[m_currentCursor]->GetTransform());
            m_currentCursor++;
        }
    }

    //----- 決定
    if (IsKeyTrigger(KEY_BUTTON)) {
        //----- 範囲外チェック
        if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
            //----- 範囲外。何もしない
        }
        else {
            //----- 範囲内。関数を実行する
            m_children[m_currentCursor]->GetComponent<MenuGameObjectClient>()->Action();
        }
    }

    //----- 位置設定
    if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
        //----- 範囲外。サイズをゼロにして描画しないようにする
        m_gameObject->SetTransform(Transform({ 0,0,0 }, { 0,0,0 }));
    }
    else {
        //----- 範囲内。位置を設定する
        auto transofrm = m_children[m_currentCursor]->GetTransform();
        transofrm.pos.x  -= transofrm.size.x;
        transofrm.size.x /= 2;
        transofrm.pos.x  += transofrm.size.x / 2;
        m_gameObject->SetTransform(transofrm);
    }
}


// ゲームオブジェクトを追加する
void MenuGameObjectControl::AddGameObject(GameObject *gameObject) {
    //----- クライアントが追加されているか
    if (gameObject->GetComponent<MenuGameObjectClient>() == nullptr) throw std::exception("Errer! MenuGameObjectClient not attached");

    //----- ゲームオブジェクトの追加
    m_children.push_back(gameObject);
}


void MenuGameObject::Prefab(void) {
    //----- ステータス設定
    SetName(NAME_MENU);
    SetTransform(Transform({ 0,0,0 }, { 0,0,0 }));

    //----- コンポーネントの追加
    AddComponent<MenuGameObjectControl>();
    auto sprite = new SpriteShowComponent(this, LOAD_CURSOR_FILENAME);
    AddComponent(sprite);
}
