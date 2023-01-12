#include <DXGame/Player.h>
#include <DXGame/GameDefine.h>
#include <DXGame/HP.h>
#include <DXGame/Input.h>
#include <DXGame/ModelComponent.h>
#include <DXGame/CameraSystem.h>
#include <DXGame/CameraBase.h>
#include <DXGame/FileStorage.h>
#include <DXGame/Collsion.h>
#include <DXGame/SceneMoveButton.h>
#include <DXGame/Result.h>


const float PLAYER_AUTO_MOVE_SPEED_DEFAULT = 0.75f;     // �O���ւ̈ړ����x
const float PLAYER_AUTO_MOVE_SPEED_ADD     = 0.003f;    // �O���ւ̈ړ����x�����l
const float PLAYER_MOVE_SPEED      = 1.0f;   // �v���C���[�̍��E�ւ̈ړ����x
const float PLAYER_MOVE_MAX        = 17.5f;  // ���E�ړ����


void PlayerControl::Start(void) {
    //----- ���x������
    PlayerSpeedManager::Get()->SetSpeed(PLAYER_AUTO_MOVE_SPEED_DEFAULT);

    //----- Polyline������
    m_polyline = std::unique_ptr<GeometoryPolyline>(new GeometoryPolyline(30));
    m_polyline->SetTexture(FileStorage::Get()->LoadTexture("Foo.png"));
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
        pos.pos.x += PLAYER_MOVE_SPEED;
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
    if (m_gameObject->GetTransform().pos.x >   PLAYER_MOVE_MAX ) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x =   PLAYER_MOVE_MAX ;
        m_gameObject->SetTransform(pos);
    }

    //----- �O�i
    {
        auto pos = m_gameObject->GetTransform();
        pos.pos.z += PlayerSpeedManager::Get()->GetSpeed();
        m_gameObject->SetTransform(pos);
    }

    //----- ����
    PlayerSpeedManager::Get()->SetSpeed(PlayerSpeedManager::Get()->GetSpeed() + PLAYER_AUTO_MOVE_SPEED_ADD);

    //----- ���g�����S���Ă�����폜
    if (m_gameObject->GetComponent<HP>()->IsDead()) {
        //----- Result�ړ��p�{�^������
        auto button = m_gameObject->GetScene()->CreatePrefab<GameObject>(Transform({ 0,0,0 }, { 1,1,1 }));
        auto* buttonComp = new SceneMoveButton<Result>(button, LOAD_RESULT_BUTTON_FILENAME);
        button->AddComponent(buttonComp);

        //----- �폜����
        PlayerSpeedManager::Get()->SetSpeed(0.f);
        m_gameObject->DeleteGameObject();
    }
}
void PlayerControl::Collsion(void) {
    auto data = m_gameObject->GetCollsionData();
    for (auto& it : data.list) {
        if (it.hitCollsion->GetTag() == Tag::Ground) {
            m_gameObject->GetComponent<HP>()->Damage(m_gameObject->GetComponent<HP>()->GetHP());
        }
    }
}
void PlayerControl::Draw(void) {
    //----- �|�����C���̃|�C���g�ǉ�
    GeometoryPolyline::Point point;
    point.pos = m_gameObject->GetTransform().pos;  // �v���C���[�̈ʒu
    point.width = 01.0f; // �|�����C���̕�

    //----- �J�����Ɍ������@�����v�Z
    DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&CameraSystem::Get()->GetCamera()->GetGameObject()->GetTransform().pos);
    DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_gameObject->GetTransform().pos);
    DirectX::XMStoreFloat3(&point.normal, DirectX::XMVectorSubtract(vCamPos, vPos));
    m_polyline->PushPoint(point);
    //----- �|�����C���̕\��
    m_polyline->SetView(CameraSystem::Get()->GetCamera()->GetViewMatrix());
    m_polyline->SetProjection(CameraSystem::Get()->GetCamera()->GetProjectionMatrix());
    m_polyline->Draw();
}


void Player::Prefab(void) {
    //----- �I�u�W�F�N�g�ݒ�
    SetName(NAME_PLAYER);

    //----- �����蔻��̒ǉ�
    AddCollsion(false, DirectX::XMFLOAT3(3, 5, 3));

    //----- ���f���R���|�[�l���g�̒ǉ�
    auto* model = new ModelComponent(this, LOAD_PLAYER_FILENAME, LOAD_PLAYER_SCALE);

    //----- �R���|�[�l���g�̒ǉ�
    AddComponent(model);
    AddComponent<HP>();
    AddComponent<PlayerControl>();
}
