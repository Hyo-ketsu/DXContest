#include <DXGame/Player.h>
#include <DXGame/GameDefine.h>
#include <DXGame/HP.h>
#include <DXGame/Input.h>
#include <DXGame/ModelComponent.h>


const float PLAYER_AUTO_MOVE_SPEED = 0.25;  // �O���ւ̈ړ����x
const float PLAYER_MOVE_SPEED      = 0.5f;  // �v���C���[�̍��E�ւ̈ړ����x
const float PLAYER_MOVE_MAX        = 2.0f;  // ���E�ړ����
const std::string PLAYER_FILENAME = "Unitychan/unitychan.fbx";  // �ǂݍ��݃t�@�C����


void PlayerControl::Start(void) {

}
void PlayerControl::Update(void) {
    //----- ���E�ړ�
    // ���ړ�
    if (IsKeyPress('A') || IsKeyPress(VK_LEFT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x -= PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }
    // �E�ړ�
    if (IsKeyPress('D') || IsKeyPress(VK_RIGHT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x -= PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }

    //----- ���E�ړ�����␳
    // ���␳
    if (m_gameObject->GetTransform().pos.x < -(PLAYER_MOVE_MAX)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x = -(PLAYER_MOVE_MAX);
        m_gameObject->SetTransform(pos);
    }
    // �E�␳
    if (m_gameObject->GetTransform().pos.x <   PLAYER_MOVE_MAX ) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x =   PLAYER_MOVE_MAX ;
        m_gameObject->SetTransform(pos);
    }

    //----- �O�i
    {
        auto pos = m_gameObject->GetTransform();
        pos.pos.z += PLAYER_AUTO_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }

    //----- ���g�����S���Ă�����폜
    if (m_gameObject->GetComponent<HP>()->IsDead()) {
        m_gameObject->DeleteGameObject();
    }
}


void Player::Prefab(void) {
    //----- �I�u�W�F�N�g�ݒ�
    SetName(NAME_PLAYER);

    //----- ���f���R���|�[�l���g�̒ǉ�
    auto* model = new ModelComponent(this, PLAYER_FILENAME, 0.05);

    //----- �R���|�[�l���g�̒ǉ�
    AddComponent(model);
    AddComponent<HP>();
    AddComponent<PlayerControl>();
}
