#include <DXGame/CollsionSystem.h>


// �����蔻��̒ǉ�
void CollsionSystem::AddCollsion(Collsion* collsion) {
    m_collsion.push_back(collsion);
}
// �����蔻��̍폜
void CollsionSystem::DeleteCollsion(Collsion* collsion) {
    //----- �����|�C���^�̌���
    for (auto it = m_collsion.begin(); it != m_collsion.end(); it++) {
        if (*it == collsion) {
            //----- �����|�C���^�B�폜
            m_collsion.erase(it);
            return;
        }
    }
}


// �S�Ă̓����蔻��𔻒肷��
void CollsionSystem::AllCollsionHit(void) {

}
