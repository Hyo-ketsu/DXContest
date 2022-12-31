#include "Collsion.h"
#include <float.h>

const bool IsCheckEqualFloat(const float& float1, const float& float2 = 0.0f) {
    return fabsf(float1 - float2) <= FLT_EPSILON ? true : false;
}

Collision::Result Collision::CheckRayPlane(Ray ray, Plane plane) {
    Result result = {};

    DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);
    DirectX::XMVECTOR vRayN     = DirectX::XMLoadFloat3(&ray.direction);
    DirectX::XMVECTOR vPlaneN   = DirectX::XMLoadFloat3(&plane.normal);
    DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);
    vRayN   = DirectX::XMVector3Normalize(vRayN);
    vPlaneN = DirectX::XMVector3Normalize(vPlaneN);

    //----- ���ʂ���n�_�܂ł̋���
    float P1;
    DirectX::XMVECTOR vToStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
    DirectX::XMStoreFloat(&P1, DirectX::XMVector3Dot(vToStart, vPlaneN));

    //----- �I�_���畽�ʂ܂ł̋���
    float P2;
    DirectX::XMVECTOR vToEnd;    
    vToEnd = DirectX::XMVectorScale(vRayN, ray.length); // �I���_�ւ̃x�N�g���̒���
    vToEnd = DirectX::XMVectorAdd(vRayStart, vToEnd);   // ���C�̏I���_�̌v�Z
    vToEnd = DirectX::XMVectorSubtract(vToEnd, vPlanePos);
    DirectX::XMStoreFloat(&P2, DirectX::XMVector3Dot(vToEnd, vPlaneN));

    //----- ���C���ʂ��ђʂ��Ă��邩
    if (P1 > 0 && P2 < 0) {
        result.hit = true;
        DirectX::XMVECTOR vStartToEnd = DirectX::XMVectorSubtract(vRayStart, DirectX::XMVectorAdd(vRayStart, DirectX::XMLoadFloat3(&plane.normal)));
        float raySize = ray.length * (P1 / (P1 + -P2));
        DirectX::XMStoreFloat3(&result.point, DirectX::XMVectorScale(vRayN, raySize));
    }

    return result;
}

//----- �`�󂲂Ƃ̓����蔻�������
Collision::Result Collision::CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle) {
    Collision::Result result = {};
    DirectX::XMVECTOR vCross[3];    // �O�ς̌v�Z����
    DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);    
    DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);
    for (int i = 0; i < 3; i++) {
        DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[i % 2]);
        DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart); // �ӂ̃x�N�g��
        DirectX::XMVECTOR vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);  // �V�Ɍ������x�N�g��
        vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
        vCross[i] = DirectX::XMVector3Normalize(vCross[i]);
        vTriStart = vTriEnd;    // ���̏I�_�����̏I�_�ƂȂ�
    }
    DirectX::XMVECTOR vDot[3] = {DirectX::XMVector3Dot(vCross[0],vCross[1]),DirectX::XMVector3Dot(vCross[1],vCross[2]),DirectX::XMVector3Dot(vCross[2],vCross[0]) };
    float match[3];
    DirectX::XMStoreFloat(&match[0], vDot[0]);
    DirectX::XMStoreFloat(&match[1], vDot[1]);
    DirectX::XMStoreFloat(&match[2], vDot[2]);
    if (match[0] >= 1.0f || IsCheckEqualFloat(match[0]) &&
        match[1] >= 1.0f || IsCheckEqualFloat(match[1]) && 
        match[2] >= 1.0f || IsCheckEqualFloat(match[2])    ) {
        result.hit = true;
        result.point = point;
    }
    return result;
}
