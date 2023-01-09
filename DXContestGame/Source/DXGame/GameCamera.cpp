#include <DXGame/GameCamera.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>


const float CAMERA_LOOK_POSTION = 8.f; //
const float CAMERA_POSTION_Y =  15;  // 注視点からのカメラ Y 位置
const float CAMERA_POSTION_Z = -30;  // 注視点からのカメラ Z 位置


#if 1
void GameCameraCamera::Start(void) {
    //----- プレイヤーの検索・取得
    Player* player = dynamic_cast<decltype(player)>(SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER));

    //----- NullCheck
    if (player == nullptr) throw std::exception("Errer! Non Player");

    //----- メインカメラ設定
    this->SetMainCamera(true);
}
void GameCameraCamera::Update(void) {
    //----- プレイヤーの検索・取得
    auto* player = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER);

    //----- プレイヤーが存在しないのであれば何もしない
    if (player == nullptr) return;

    //----- 注視点をプレイヤーに設定
    m_look.x = player->GetTransform().pos.x;
    m_look.y = player->GetTransform().pos.y + CAMERA_LOOK_POSTION;
    m_look.z = player->GetTransform().pos.z;

    //----- カメラ位置設定
    auto cameraPos = m_look;
    cameraPos.y += CAMERA_POSTION_Y;
    cameraPos.z += CAMERA_POSTION_Z;
    m_gameObject->SetTransform(cameraPos);
}


void GameCamera::Prefab(void) {
    AddComponent<GameCameraCamera>();
}
#endif


#if 0
#include <DXGame/GameCamera.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>

void GameCameraCamera::Start(void) {
    //----- プレイヤーの検索・取得
    m_player = dynamic_cast<decltype(m_player)>(SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER));

    //----- NullCheck
    if (m_player == nullptr) throw std::exception("Errer! Non Player");

    //----- メインカメラ設定
    this->SetMainCamera(true);
}
void GameCameraCamera::Update(void) {
#include <DXGame/Input.h>
    static float m_radY = 0;
    static float m_radXZ = 0;
    static float m_radius = 5;
    //-----m_radXZ カメラ回転
    if (IsKeyPress('W')) m_radY -= 0.1f;
    if (IsKeyPress('S')) m_radY += 0.1f;
    if (IsKeyPress('D')) m_radXZ -= 0.1f;
    if (IsKeyPress('A')) m_radXZ += 0.1f;

    //----- 注視点との距離を変える
    if (IsKeyPress('Q')) m_radius -= 0.5f;
    if (IsKeyPress('E')) m_radius += 0.5f;

    //----- カメラ移動
    if (IsKeyPress(VK_DOWN))  m_look.z += 0.5f;
    if (IsKeyPress(VK_UP))    m_look.z -= 0.5f;
    if (IsKeyPress(VK_LEFT))  m_look.x += 0.5f;
    if (IsKeyPress(VK_RIGHT)) m_look.x -= 0.5f;
    if (IsKeyPress(VK_SHIFT)) m_look.y += 0.5f;
    if (IsKeyPress(VK_CONTROL)) m_look.y -= 0.5f;

    //----- 角度と距離、注視点からカメラの位置を計算
    auto m_pos = m_gameObject->GetTransform();
    m_pos.pos.x = cosf(m_radY) * sinf(m_radXZ) * m_radius + m_look.x;
    m_pos.pos.y = sinf(m_radY)                 * m_radius + m_look.y;
    m_pos.pos.z = cosf(m_radY) * cosf(m_radXZ) * m_radius + m_look.z;
    m_gameObject->SetTransform(m_pos);
}


void GameCamera::Prefab(void) {
    AddComponent<GameCameraCamera>();
}
#endif
