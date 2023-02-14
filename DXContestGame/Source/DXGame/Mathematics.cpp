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
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(start), Utility::XMFLOAT3ToXMVECTOR(end));

    //----- �ԋp
    return m_lineInfo;
}


// �_���猩�����̍ł��߂��ꏊ���v�Z����
DirectX::XMFLOAT3 Mathematics::PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line) {
    //----- ���̎n�_->���̏I�_�ւ̒P�ʃx�N�g�����擾
    DirectX::XMVECTOR lineDirectionVec;     // ���̎n�_->���̏I�_�ւ̒P�ʃx�N�g��
    lineDirectionVec = DirectX::XMVector3Normalize(line.GetLineInfo().direction);

    //----- ���̎n�_->�_�ւ̃x�N�g�����擾
    DirectX::XMVECTOR lineStartToPoint;    // ���̎n�_->�_�ւ̃x�N�g��
    lineStartToPoint = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos), Utility::XMFLOAT3ToXMVECTOR(point));

    //----- ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g�����擾
    DirectX::XMVECTOR lineStartToLineNearPoint; // ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g��
    lineStartToLineNearPoint = DirectX::XMVector3Dot(lineDirectionVec, lineStartToPoint);

    //----- �_�̍��W�̌v�Z
    DirectX::XMFLOAT3 pointPos;  // �ԋp�p�_�̍��W 
    DirectX::XMStoreFloat3(&pointPos, DirectX::XMVectorAdd(
        Utility::XMFLOAT3ToXMVECTOR(point), lineStartToPoint)
    );   // ���̎n�_ + ���̎n�_->�_�ɍł��߂�����̓_�ւ̃x�N�g���œ_�̈ʒu���Z�o����

    //----- ���̏I�_�Ɠ_�̈ʒu�̔�r
    // @ Memo : �_�̈ʒu�����̏I�_���щz���Ă���ꍇ�Ax,y,z �ǂꂩ�̗v�f��
    // @ Memo : ���̏I�_�̍��W�̐�Βl < �_�̍��W�̐�Βl �ɂȂ�B
    // @ Memo : x,y,z �ǂꂩ�̗v�f����̎��𖞂����Ă����ꍇ�A���̏I�_���щz���Ă���Ɣ��f���Đ��̏I�_�̍��W���g�p����B
    if (fabsf(line.GetLineInfo().endPos.x) < fabsf(pointPos.x)) pointPos.x = line.GetLineInfo().endPos.x;
    if (fabsf(line.GetLineInfo().endPos.y) < fabsf(pointPos.y)) pointPos.y = line.GetLineInfo().endPos.y;
    if (fabsf(line.GetLineInfo().endPos.z) < fabsf(pointPos.z)) pointPos.z = line.GetLineInfo().endPos.z;

    return pointPos;
}
