#include <DXGame/CollsionSystem.h>


// 当たり判定の追加
void CollsionSystem::AddCollsion(Collsion* collsion) {
    m_collsion.push_back(collsion);
}
// 当たり判定の削除
void CollsionSystem::DeleteCollsion(Collsion* collsion) {
    //----- 同じポインタの検索
    for (auto it = m_collsion.begin(); it != m_collsion.end(); it++) {
        if (*it == collsion) {
            //----- 同じポインタ。削除
            m_collsion.erase(it);
            return;
        }
    }
}


// 全ての当たり判定を判定する
void CollsionSystem::AllCollsionHit(void) {

}
