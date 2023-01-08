#include <DXGame/Player.h>
#include <DXGame/GameDefine.h>
#include <DXGame/HP.h>
#include <DXGame/Input.h>
#include <DXGame/ModelComponent.h>


const float PLAYER_AUTO_MOVE_SPEED = 0.25;  // 前方への移動速度
const float PLAYER_MOVE_SPEED      = 0.5f;  // プレイヤーの左右への移動速度
const float PLAYER_MOVE_MAX        = 2.0f;  // 左右移動上限
const std::string PLAYER_FILENAME = "Unitychan/unitychan.fbx";  // 読み込みファイル名


void PlayerControl::Start(void) {

}
void PlayerControl::Update(void) {
    //----- 左右移動
    // 左移動
    if (IsKeyPress('A') || IsKeyPress(VK_LEFT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x -= PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }
    // 右移動
    if (IsKeyPress('D') || IsKeyPress(VK_RIGHT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x -= PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }

    //----- 左右移動上限補正
    // 左補正
    if (m_gameObject->GetTransform().pos.x < -(PLAYER_MOVE_MAX)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x = -(PLAYER_MOVE_MAX);
        m_gameObject->SetTransform(pos);
    }
    // 右補正
    if (m_gameObject->GetTransform().pos.x <   PLAYER_MOVE_MAX ) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x =   PLAYER_MOVE_MAX ;
        m_gameObject->SetTransform(pos);
    }

    //----- 前進
    {
        auto pos = m_gameObject->GetTransform();
        pos.pos.z += PLAYER_AUTO_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }

    //----- 自身が死亡していたら削除
    if (m_gameObject->GetComponent<HP>()->IsDead()) {
        m_gameObject->DeleteGameObject();
    }
}


void Player::Prefab(void) {
    //----- オブジェクト設定
    SetName(NAME_PLAYER);

    //----- モデルコンポーネントの追加
    auto* model = new ModelComponent(this, PLAYER_FILENAME, 0.05);

    //----- コンポーネントの追加
    AddComponent(model);
    AddComponent<HP>();
    AddComponent<PlayerControl>();
}
