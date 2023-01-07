#include <DXGame/Collsion.h>
#include <DXGame/CollsionSystem.h>
#include <DXGame/GameObject.h>
#include <float.h>


// �ǂ��̖ʂ�
enum class HitCollsionDirection {
    X,
    Y,
    Z,
};


// �����擾����
std::vector<CollsionHitData> CollsionHitDataVector::GetDate(const bool isProvFrameHit) {
    //----- �ԋp�p�ϐ��錾
    std::vector<CollsionHitData> ret;

    //----- ����
    for (auto& it : list) {
        if (it.isProvFrameHit == isProvFrameHit) {
            ret.push_back(it);
        }
    }

    //----- �ԋp
    return ret;
}


// �R���X�g���N�^
Collsion::Collsion(GameObject* gameObject, const bool isHitMove, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& pos)
    : m_tag(Tag::Non)
    , m_isActive(true)
    , m_isHitMove(isHitMove)
    , m_gameObject(gameObject)
    , m_pos(pos)
    , m_size(size) {
    CollsionSystem::Get()->AddCollsion(this);
}
// �f�X�g���N�^
Collsion::~Collsion(void) {
    CollsionSystem::Get()->DeleteCollsion(this);
}


// �^����ꂽ�����蔻��ƏՓ˔�����s��
void Collsion::CollsionHitCheck(const Collsion& collsion) {
    //----- �Փ˔�����s��������
    if (this->GetActive()    == false) return;
    if (collsion.GetActive() == false) return;
    if (this->GetGameObject()->GetActive()    == false) return;
    if (collsion.GetGameObject()->GetActive() == false) return;
    if (this->GetTag() == collsion.GetTag())            return;

    //----- �ϐ��錾
    DirectX::XMFLOAT3 thisTransform;    // ���g�̍��W
    DirectX::XMFLOAT3 targetTransform;  // �Փˑ���̍��W
    std::vector<HitCollsionDirection> hitDirection; // ��������������\��

    //----- ������
    thisTransform.x = m_pos.x + m_gameObject->GetTransform().pos.x;
    thisTransform.y = m_pos.y + m_gameObject->GetTransform().pos.y;
    thisTransform.z = m_pos.z + m_gameObject->GetTransform().pos.z;
    targetTransform.x = collsion.m_pos.x + collsion.GetGameObject()->GetTransform().pos.x;
    targetTransform.y = collsion.m_pos.y + collsion.GetGameObject()->GetTransform().pos.y;
    targetTransform.z = collsion.m_pos.z + collsion.GetGameObject()->GetTransform().pos.z;

    //----- ����
    //----- �Ώ� +X �ʔ���
    if (thisTransform.x - m_size.x / 2 < targetTransform.x + collsion.m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x + collsion.m_size.x / 2)
    {
        hitDirection.push_back(HitCollsionDirection::X);
    }
    //----- �Ώ� -X �ʔ���
    if (thisTransform.x - m_size.x / 2 < targetTransform.x - collsion.m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x - collsion.m_size.x / 2)
    {
        hitDirection.push_back(HitCollsionDirection::X);
    }
    //----- �Ώ� +Y �ʔ���
    if (thisTransform.y - m_size.y / 2 < targetTransform.y + collsion.m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y + collsion.m_size.y / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Y);
    }
    //----- �Ώ� -Y �ʔ���
    if (thisTransform.y - m_size.y / 2 < targetTransform.y - collsion.m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y - collsion.m_size.y / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Y);
    }
    //----- �Ώ� +Z �ʔ���
    if (thisTransform.z - m_size.z / 2 < targetTransform.z + collsion.m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z + collsion.m_size.z / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Z);
    }
    //----- �Ώ� -Z �ʔ���
    if (thisTransform.z - m_size.z / 2 < targetTransform.z - collsion.m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z - collsion.m_size.z / 2)
    {
        hitDirection.push_back(HitCollsionDirection::Z);
    }

    //----- �����߂��p�ϐ��錾
    float thisRemove = 0.0f;    // �����߂����i�j
    float targetRemove = 0.0f;  // �����߂����i�j

    //----- �����߂����ݒ�
    if (m_isHitMove && collsion.m_isHitMove) {
        //----- �ǂ���Ƃ������߂����s��
        thisRemove = 0.5f;
        targetRemove = 0.5f;
    }
    else {
        if (m_isHitMove) {
            //----- ���g�͈����߂����s��
            thisRemove = 1.0f;
            targetRemove = 0.0f;
        }
        if (collsion.m_isHitMove) {
            //----- �Ώۂ͈����߂����s��
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
//    //----- ���ʂ���n�_�܂ł̋���
//    float P1;
//    DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
//    DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vToStart, vPlaneN));
//
//    //----- �I�_���畽�ʂ܂ł̋���
//    float P2;
//    DirectX::XMVECTOR vToEnd;    
//    vToEnd = DirectX::XMVectorScale(vRayN, ray.length); // �I���_�ւ̃x�N�g���̒���
//    vToEnd = DirectX::XMVectorAdd(vRayStart, vToEnd);   // ���C�̏I���_�̌v�Z
//    vToEnd = DirectX::XMVectorSubtract(vToEnd, vPlanePos);
//    DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vToEnd, vPlaneN));
//
//    //----- ���C���ʂ��ђʂ��Ă��邩
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
////----- �`�󂲂Ƃ̓����蔻�������
//Collision::Result Collision::CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle) {
//    Collision::Result result = {};
//    DirectX::XMVECTOR vCross[3];    // �O�ς̌v�Z����
//    DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);    
//    DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);
//    for (int i = 0; i < 3; i++) {
//        DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[i % 2]);
//        DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart); // �ӂ̃x�N�g��
//        DirectX::XMVECTOR vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);  // �V�Ɍ������x�N�g��
//        vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
//        vCross[i] = DirectX::XMVector3Normalize(vCross[i]);
//        vTriStart = vTriEnd;    // ���̏I�_�����̏I�_�ƂȂ�
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
