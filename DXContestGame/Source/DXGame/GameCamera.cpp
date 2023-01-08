#include <DXGame/GameCamera.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>


const float CAMERA_LOOK_POSTION = 7.5f; //
const float CAMERA_POSTION_Y = -5;   // �����_����̃J���� Y �ʒu
const float CAMERA_POSTION_Z = -20;  // �����_����̃J���� Z �ʒu


void GameCameraCamera::Start(void) {
    //----- �v���C���[�̌����E�擾
    m_player = dynamic_cast<decltype(m_player)>(SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER));

    //----- NullCheck
    if (m_player == nullptr) throw std::exception("Errer! Non Player");

    //----- ���C���J�����ݒ�
    this->SetMainCamera(true);
}
void GameCameraCamera::Update(void) {
    //----- �����_���v���C���[�ɐݒ�
    m_look.x = m_player->GetTransform().pos.x;
    m_look.y = m_player->GetTransform().pos.y + CAMERA_LOOK_POSTION;
    m_look.z = m_player->GetTransform().pos.z;

    //----- �J�����ʒu�ݒ�
    auto cameraPos = m_look;
    cameraPos.y += CAMERA_POSTION_Y;
    cameraPos.z += CAMERA_POSTION_Z;
    m_gameObject->SetTransform(cameraPos);
}


void GameCamera::Prefab(void) {
    AddComponent<GameCameraCamera>();
}
