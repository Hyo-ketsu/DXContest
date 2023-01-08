#include <DXGame/HP.h>


// ƒ_ƒ[ƒW‚ğ—^‚¦‚é
void HP::Damage(const int damage) {
    m_hp -= damage;
    if (m_hp < 0) m_hp = 0;
}


// ¶€”»’è
const bool HP::IsDead(void) const {
    return m_hp < 1 ? true : false;
}
