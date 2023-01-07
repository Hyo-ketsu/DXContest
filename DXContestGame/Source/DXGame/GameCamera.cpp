#include <DXGame/GameCamera.h>


void GameCameraCamera::Start(void) {
    this->SetMainCamera(true);
}
void GameCameraCamera::Update(void) {
    m_look.x = m_gameObject->GetTransform().pos.x;
    m_look.y = m_gameObject->GetTransform().pos.y - 5;
    m_look.z = m_gameObject->GetTransform().pos.z - 15;
}


void GameCamera::Prefab(void) {
    AddComponent<GameCameraCamera>();
}
