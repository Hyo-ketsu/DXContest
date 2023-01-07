#include <DXGame/Collsion.h>
#include <DXGame/CollsionSystem.h>
#include <DXGame/GameObject.h>
#include <float.h>


// どこの面か
enum class HitCollsionDirection {
    X,
    Y,
    Z,
};


// 情報を取得する
std::vector<CollsionHitData> CollsionHitDataVector::GetDate(const bool isProvFrameHit) {
    //----- 返却用変数宣言
    std::vector<CollsionHitData> ret;

    //----- 検索
    for (auto& it : list) {
        if (it.isProvFrameHit == isProvFrameHit) {
            ret.push_back(it);
        }
    }

    //----- 返却
    return ret;
}


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
void Collsion::CollsionHitCheck(const Collsion& collsion) {
    //----- 衝突判定を行うか判定
    if (this->GetActive()    == false) return;
    if (collsion.GetActive() == false) return;
    if (this->GetGameObject()->GetActive()    == false) return;
    if (collsion.GetGameObject()->GetActive() == false) return;
    if (this->GetTag() == collsion.GetTag())            return;

    //----- 変数宣言
    DirectX::XMFLOAT3 thisTransform;    // 自身の座標
    DirectX::XMFLOAT3 targetTransform;  // 衝突相手の座標
    std::vector<HitCollsionDirection> hitDirection; // 当たった方向を表す

    //----- 初期化
    thisTransform.x = m_pos.x + m_gameObject->GetTransform().pos.x;
    thisTransform.y = m_pos.y + m_gameObject->GetTransform().pos.y;
    thisTransform.z = m_pos.z + m_gameObject->GetTransform().pos.z;
    targetTransform.x = collsion.m_pos.x + collsion.GetGameObject()->GetTransform().pos.x;
    targetTransform.y = collsion.m_pos.y + collsion.GetGameObject()->GetTransform().pos.y;
    targetTransform.z = collsion.m_pos.z + collsion.GetGameObject()->GetTransform().pos.z;

    //----- 判定
    //----- 対象 +X 面判定
    if (thisTransform.x - m_size.x / 2 < targetTransform.x + collsion.m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x + collsion.m_size.x / 2)
    {
        hitDirection.push_back(HitCollsionDirection::X);
    }
    //----- 対象 -X 面判定
    if (thisTransform.x - m_size.x / 2 < targetTransform.x - collsion.m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x - collsion.m_size.x / 2)
    {
        hitDirection.push_back(HitCollsionDirection::X);
    }
    //----- 対象 +Y 面判定
    if (thisTransform.y - m_size.y / 2 < targetTransform.y + collsion.m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y + collsion.m_size.y / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Y);
    }
    //----- 対象 -Y 面判定
    if (thisTransform.y - m_size.y / 2 < targetTransform.y - collsion.m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y - collsion.m_size.y / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Y);
    }
    //----- 対象 +Z 面判定
    if (thisTransform.z - m_size.z / 2 < targetTransform.z + collsion.m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z + collsion.m_size.z / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Z);
    }
    //----- 対象 -Z 面判定
    if (thisTransform.z - m_size.z / 2 < targetTransform.z - collsion.m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z - collsion.m_size.z / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Z);
    }

    //----- 引き戻し用変数宣言
    float thisRemove = 0.0f;    // 引き戻し率（）
    float targetRemove = 0.0f;  // 引き戻し率（）

    //----- 引き戻し率設定
    if (m_isHitMove && collsion.m_isHitMove) {
        //----- どちらとも引き戻しを行う
        thisRemove = 0.5f;
        targetRemove = 0.5f;
    }
    else {
        if (m_isHitMove) {
            //----- 自身は引き戻しを行う
            thisRemove = 1.0f;
            targetRemove = 0.0f;
        }
        if (collsion.m_isHitMove) {
            //----- 対象は引き戻しを行う
            thisRemove = 0.0f;
            targetRemove = 1.0f;
        }
    }

}


//const bool IsCheckEqualFloat(const float& float1, const float& float2 = 0.0f) {
//    return fabsf(float1 - float2) <= FLT_EPSILON ? true : false;
//}
//
//Collision::Result Collision::CheckRayPlane(Ray ray, Plane plane) {
//    Result result = {};
//
//    DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);
//    DirectX::XMVECTOR vRayN     = DirectX::XMLoadFloat3(&ray.direction);
//    DirectX::XMVECTOR vPlaneN   = DirectX::XMLoadFloat3(&plane.normal);
//    DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);
//    vRayN   = DirectX::XMVector3Normalize(vRayN);
//    vPlaneN = DirectX::XMVector3Normalize(vPlaneN);
//
//    //----- 平面から始点までの距離
//    float P1;
//    DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
//    DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vToStart, vPlaneN));
//
//    //----- 終点から平面までの距離
//    float P2;
//    DirectX::XMVECTOR vToEnd;    
//    vToEnd = DirectX::XMVectorScale(vRayN, ray.length); // 終了点へのベクトルの長さ
//    vToEnd = DirectX::XMVectorAdd(vRayStart, vToEnd);   // レイの終了点の計算
//    vToEnd = DirectX::XMVectorSubtract(vToEnd, vPlanePos);
//    DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vToEnd, vPlaneN));
//
//    //----- レイが面を貫通しているか
//    if (P1 > 0 && P2 < 0) {
//        result.hit = true;
//        DirectX::XMVECTOR vStartToEnd = DirectX::XMVectorSubtract(vRayStart, DirectX::XMVectorAdd(vRayStart, DirectX::XMLoadFloat3(&plane.normal)));
//        float raySize = ray.length * (P1 / (P1 + -P2));
//        DirectX::XMStoreFloat3(&result.point, DirectX::XMVectorScale(vRayN, raySize));
//    }
//
//    return result;
//}
//
////----- 形状ごとの当たり判定を実装
//Collision::Result Collision::CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle) {
//    Collision::Result result = {};
//    DirectX::XMVECTOR vCross[3];    // 外積の計算結果
//    DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);    
//    DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);
//    for (int i = 0; i < 3; i++) {
//        DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[i % 2]);
//        DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart); // 辺のベクトル
//        DirectX::XMVECTOR vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);  // 天に向かうベクトル
//        vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
//        vCross[i] = DirectX::XMVector3Normalize(vCross[i]);
//        vTriStart = vTriEnd;    // 今の終点が次の終点となる
//    }
//    DirectX::XMVECTOR vDot[3] = {DirectX::XMVector3Dot(vCross[0],vCross[1]),DirectX::XMVector3Dot(vCross[1],vCross[2]),DirectX::XMVector3Dot(vCross[2],vCross[0]) };
//    float match[3];
//    DirectX::XMStoreFloat(&match[0], vDot[0]);
//    DirectX::XMStoreFloat(&match[1], vDot[1]);
//    DirectX::XMStoreFloat(&match[2], vDot[2]);
//    if (match[0] >= 1.0f || IsCheckEqualFloat(match[0]) &&
//        match[1] >= 1.0f || IsCheckEqualFloat(match[1]) && 
//        match[2] >= 1.0f || IsCheckEqualFloat(match[2])    ) {
//        result.hit = true;
//        result.point = point;
//    }
//    return result;
//}
