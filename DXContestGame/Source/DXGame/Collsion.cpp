#include <DXGame/Collsion.h>
#include <DXGame/CollsionSystem.h>
#include <DXGame/GameObject.h>
#include <float.h>
#include <array>


// どこの面か
enum HitCollsionDirection {
    X = 0,
    Y,
    Z,
};


// コンストラクタ
Collsion::Collsion(GameObject* gameObject, const bool isHitMove, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& pos)
    : m_tag(Tag::Non)
    , m_isActive(true)
    , m_isHitMove(isHitMove)
    , m_gameObject(gameObject)
    , m_pos(pos)
    , m_size(size) {
    CollsionSystem::Get()->AddCollsion(this);
}
// デストラクタ
Collsion::~Collsion(void) {
    CollsionSystem::Get()->DeleteCollsion(this);
}


// 与えられた当たり判定と衝突判定を行う
const bool Collsion::CollsionHitCheck(const DirectX::XMFLOAT3 thisTransform, Collsion* const collsion) {
    //----- 衝突判定を行うか判定
    if (this->GetActive()     == false) return false;
    if (collsion->GetActive() == false) return false;
    if (this->GetGameObject()->GetActive()     == false) return false;
    if (collsion->GetGameObject()->GetActive() == false) return false;
    if (this == collsion)                                return false;
    if (this->GetTag() == collsion->GetTag())            return false;

    //----- 変数宣言
    DirectX::XMFLOAT3 targetTransform;  // 衝突相手の座標
    std::array<bool,3> hitDirection;    // 当たった方向を表す
    hitDirection.fill(false);

    //----- 初期化
    targetTransform.x = collsion->m_pos.x + collsion->GetGameObject()->GetTransform().pos.x;
    targetTransform.y = collsion->m_pos.y + collsion->GetGameObject()->GetTransform().pos.y;
    targetTransform.z = collsion->m_pos.z + collsion->GetGameObject()->GetTransform().pos.z;

    //----- 判定
    //----- 対象 +X 面判定
    if (thisTransform.x - m_size.x / 2 < targetTransform.x + collsion->m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x + collsion->m_size.x / 2)
    {
        hitDirection.at(HitCollsionDirection::X) = true;
    }
    //----- 対象 -X 面判定
    if (thisTransform.x - m_size.x / 2 < targetTransform.x - collsion->m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x - collsion->m_size.x / 2)
    {
        hitDirection.at(HitCollsionDirection::X) = true;
    }
    //----- 対象 +Y 面判定
    if (thisTransform.y - m_size.y / 2 < targetTransform.y + collsion->m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y + collsion->m_size.y / 2)
    {
        hitDirection.at(HitCollsionDirection::Y) = true;
    }
    //----- 対象 -Y 面判定
    if (thisTransform.y - m_size.y / 2 < targetTransform.y - collsion->m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y - collsion->m_size.y / 2)
    {
        hitDirection.at(HitCollsionDirection::Y) = true;
    }
    //----- 対象 +Z 面判定
    if (thisTransform.z - m_size.z / 2 < targetTransform.z + collsion->m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z + collsion->m_size.z / 2)
    {
        hitDirection.at(HitCollsionDirection::Z) = true;
    }
    //----- 対象 -Z 面判定
    if (thisTransform.z - m_size.z / 2 < targetTransform.z - collsion->m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z - collsion->m_size.z / 2)
    {
        hitDirection.at(HitCollsionDirection::Z) = true;
    }

    //----- 判定返却
    if (hitDirection.at(HitCollsionDirection::X) && hitDirection.at(HitCollsionDirection::Y) && hitDirection.at(HitCollsionDirection::Z)) {
        //----- 衝突している。衝突情報を追加
        auto data = m_gameObject->GetCollsionData();
        auto coll = CollsionHitData();
        coll.hitCollsion = collsion;
        data.list.push_back(coll);
        m_gameObject->SetCollsionData(data);

        return false;
    }
    else {
        //----- 衝突していない。そのまま終了
        return true;
    }

    ////----- 引き戻し用変数宣言
    //float thisRemove = 0.0f;    // 引き戻し率（）
    //float targetRemove = 0.0f;  // 引き戻し率（）

    ////----- 引き戻し率設定
    //if (m_isHitMove && collsion.m_isHitMove) {
    //    //----- どちらとも引き戻しを行う
    //    thisRemove = 0.5f;
    //    targetRemove = 0.5f;
    //}
    //else {
    //    if (m_isHitMove) {
    //        //----- 自身は引き戻しを行う
    //        thisRemove = 1.0f;
    //        targetRemove = 0.0f;
    //    }
    //    if (collsion.m_isHitMove) {
    //        //----- 対象は引き戻しを行う
    //        thisRemove = 0.0f;
    //        targetRemove = 1.0f;
    //    }
    //}
}
