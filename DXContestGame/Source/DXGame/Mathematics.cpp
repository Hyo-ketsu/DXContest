#include <DXGame/Mathematics.h>
#include <DXGame/Utility.h>


// �R���X�g���N�^
Mathematics::LineInfoClass::LineInfoClass(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end)
    : m_lineInfo(CreateLineInfo(start,end)) {
}


// ������o�^����
Mathematics::LineInfo Mathematics::LineInfoClass::CreateLineInfo(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end) {
    //----- ���W�o�^
    m_lineInfo.startPos = start;
    m_lineInfo.endPos   = end;

    //----- �����o�^
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(end), Utility::XMFLOAT3ToXMVECTOR(start));

    //----- �ԋp
    return m_lineInfo;
}


// �_���猩�����̍ł��߂��ꏊ���v�Z����
DirectX::XMFLOAT3 Mathematics::PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line) {
    //----- ���̕����� {0,0,0} ��������i���ł͂Ȃ��_�ɂȂ��Ă���j���̎n�_��ԋp
    if (DirectX::XMVector3Equal(line.GetLineInfo().direction, DirectX::XMVectorZero())) {
        //----- ���̎n�_��ԋp
        return line.GetLineInfo().startPos;
    }

    //----- ���̎n�_->���̏I�_�ւ̒P�ʃx�N�g�����擾
    DirectX::XMVECTOR lineDirectionVec;     // ����v�n�_->���̏I�_�ւ̒P�ʃx�N�g��
    lineDirectionVec = DirectX::XMVector3Normalize(line.GetLineInfo().direction);

    //----- ���̎n�_->�_�ւ̃x�N�g�����擾
    DirectX::XMVECTOR lineStartToPoint;    // ���̎n�_->�_�ւ̃x�N�g��
    lineStartToPoint = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(point), Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos));

    //----- ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g�����擾
    DirectX::XMVECTOR lineStartToLineNearPoint; // ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g��
    for (int i = 0; i < 3; i++) {   // �e������
        lineStartToLineNearPoint.m128_f32[i] = lineDirectionVec.m128_f32[i] * lineStartToPoint.m128_f32[i];
    }
    lineStartToLineNearPoint.m128_f32[3] = 0.f;

    //----- �_�̍��W�̌v�Z
    DirectX::XMFLOAT3 pointPos;  // �ԋp�p�_�̍��W 
    DirectX::XMStoreFloat3(&pointPos, DirectX::XMVectorSubtract(
        Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos), lineStartToLineNearPoint)
    );   // ���̎n�_ + ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g���œ_�̈ʒu���Z�o����

    //----- �����Ɏ��߂�
    do {
        //----- Using�f�B���N�e�B�u
        using namespace Utility;

        //----- �ϐ��錾
        bool isFas = false; // �Ώ̓_��艓����

        //----- �������v�Z
        // @ Memo : ���������덷���C�ɂȂ�
        isFas |= XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, line.GetLineInfo().endPos)) <
                 XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, pointPos));    // �n�_����̋����v�Z
        isFas |= XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos, line.GetLineInfo().startPos)) <
                 XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos, pointPos));      // �I�_����̋����v�Z
        if (isFas == false) break;  // �����B������I������

        //----- �n�_�E�I�_���W���
        if (XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, pointPos)) <
            XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos,   pointPos))   ) {
            //----- �n�_�̂ق����߂��B�n�_���W���
            pointPos = line.GetLineInfo().startPos;
        }
        else {
            //----- �I�_�̂ق����߂��B�I�_���W���
            pointPos = line.GetLineInfo().endPos;
        }
    } while (false);

    //----- �ԋp
    return pointPos;
}
