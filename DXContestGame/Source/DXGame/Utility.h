#ifndef ____UTILITY_H____
#define ____UTILITY_H____


namespace Utility {
    // ���������������
    // @ Ret  : ������̕�����
    // @ Arg1 : ������
    // @ Arg2 : ������
    const std::string MergeString(const std::string& string1, const std::string& string2);


    // float�ϐ� �� float�ϐ����������ǂ������肷��
    // @ Ret  : ������
    // @ Arg1 : float�ϐ�
    // @ Arg2 : float�ϐ��i�f�t�H���g�F0.f�j
    const bool FloatComparison(const float float1, const float float2 = 0.f);


    // �x���i�K�j�����W�A���ɕϊ����鎮
    const float GetRad(const float rad);


    // XMFLOAT3��XMVECTOR�ɕϊ�����֐�
    DirectX::XMVECTOR XMFLOAT3ToXMVECTOR(const DirectX::XMFLOAT3& xmfloat3);


    // FLOAT3�̌��Z���s��
    // @ Ret  : ��
    // @ Arg1 : ���Z�����l
    // @ Arg1 : ���Z����l
    const DirectX::XMFLOAT3 XMFLOAT3Subtract(const DirectX::XMFLOAT3& xmfloat1, const DirectX::XMFLOAT3& xmfloat2);


    // FLOAT3�̒������v�Z���܂�
    // @ Memo : �e�v�f�̐�Βl�̍��v�ł�
    // @ Ret  : ����
    // @ Arg1 : �������v�Z����f�[�^
    const float XMFLOAT3Length(const DirectX::XMFLOAT3& xmfloat);
}


#endif // !____UTILITY_H____
