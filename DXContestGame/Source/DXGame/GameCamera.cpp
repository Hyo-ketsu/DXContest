#include <DXGame/GameCamera.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>


const float CAMERA_LOOK_POSTION = 7.5f; //
const float CAMERA_POSTION_Y = -5;   // 注視点からのカメラ Y 位置
const float CAMERA_POSTION_Z = -20;  // 注視点からのカメラ Z 位置


void GameCameraCamera::Start(void) {
    //----- プレイヤーの検索・取得
    m_player = dynamic_cast<decltype(m_player)>(SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER));

    //----- NullCheck
    if (m_player == nullptr) throw std::exception("Errer! Non Player");

    //----- メインカメラ設定
    this->SetMainCamera(true);
}
void GameCameraCamera::Update(void) {
    //----- 注視点をプレイヤーに設定
    m_look.x = m_player->GetTransform().pos.x;
    m_look.y = m_player->GetTransform().pos.y + CAMERA_LOOK_POSTION;
    m_look.z = m_player->GetTransform().pos.z;

    //----- カメラ位置設定
    auto cameraPos = m_look;
    cameraPos.y += CAMERA_POSTION_Y;
    cameraPos.z += CAMERA_POSTION_Z;
    m_gameObject->SetTransform(cameraPos);
}


void GameCamera::Prefab(void) {
    AddComponent<GameCameraCamera>();
}
