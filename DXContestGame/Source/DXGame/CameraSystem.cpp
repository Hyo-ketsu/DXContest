#include <DXGame/CameraSystem.h>


// �J������o�^����
void CameraSystem::AddCamera(CameraBase* camera) {
    m_camera.push_back(camera);
}
// �J�����̓o�^���폜����
void CameraSystem::DeleteCamera(CameraBase* camera) {
    //----- ���|�C���^�폜
    for (auto it = m_camera.begin(); it != m_camera.end(); it++) {
        if (*it == camera) {
            m_camera.erase(it);
            return;
        }
    }
}


// �J�������擾����
CameraBase const* CameraSystem::GetCamera(void) const {
    //----- �J�������p�ӂ���Ă��邩
    if (m_camera.empty()) throw std::exception("Exception! Camera does not exist!");

    //----- ���C���J�����{��
    for (auto& it : m_camera) {
        //----- ���̃J���������C���J�����ɐݒ肳��Ă���΂����ԋp����
        if (it->GetMainCamera()) return it;
    }

    //----- ���C���J�������Ȃ��B�擪�ԋp
    return m_camera.front();
}
