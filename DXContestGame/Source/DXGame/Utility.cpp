#include <DXGame/Utility.h>


// ���������������
const std::string Utility::MergeString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


// float�ϐ� �� float�ϐ����������ǂ������肷��
const bool Utility::FloatComparison(const float float1, const float float2) {
    return fabsf(float1 - float2) <= FLT_EPSILON ? true : false;
}


// �x���i�K�j�����W�A���ɕϊ����鎮
const float Utility::GetRad(const float rad) {
    return rad * 3.14f / 180;
}


// XMFLOAT3��XMVECTOR�ɕϊ�����֐�
DirectX::XMVECTOR Utility::XMFLOAT3ToXMVECTOR(const DirectX::XMFLOAT3& xmfloat3) {
    return DirectX::XMLoadFloat3(&xmfloat3);
}
