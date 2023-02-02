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
    return Mathematics::LineInfo();

    //----- �����o�^
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.startPos), Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.endPos));
}
