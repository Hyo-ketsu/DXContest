#include <DXGame/CameraSystem.h>


// カメラを登録する
void CameraSystem::AddCamera(CameraBase* camera) {
    m_camera.push_back(camera);
}
// カメラの登録を削除する
void CameraSystem::DeleteCamera(CameraBase* camera) {
    //----- 同ポインタ削除
    for (auto it = m_camera.begin(); it != m_camera.end(); it++) {
        if (*it == camera) {
            m_camera.erase(it);
            return;
        }
    }
}


// カメラを取得する
CameraBase const* CameraSystem::GetCamera(void) const {
    //----- カメラが用意されているか
    if (m_camera.empty()) throw std::exception("Exception! Camera does not exist!");

    //----- メインカメラ捜索
    for (auto& it : m_camera) {
        //----- このカメラがメインカメラに設定されていればそれを返却する
        if (it->GetMainCamera()) return it;
    }

    //----- メインカメラがない。先頭返却
    return m_camera.front();
}
