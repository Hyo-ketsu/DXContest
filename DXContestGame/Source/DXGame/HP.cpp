#include <DXGame/HP.h>


// �_���[�W��^����
void HP::Damage(const int damage) {
    m_hp -= damage;
    if (m_hp < 0) m_hp = 0;
}


// ��������
const bool HP::IsDead(void) const {
    return m_hp < 1 ? true : false;
}
