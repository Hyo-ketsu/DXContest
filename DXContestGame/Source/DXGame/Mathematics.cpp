#include <DXGame/Mathematics.h>
#include <DXGame/Utility.h>


// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Mathematics::LineInfoClass::LineInfoClass(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end)
    : m_lineInfo(CreateLineInfo(start,end)) {
}


// üî•ñ‚ğ“o˜^‚·‚é
Mathematics::LineInfo Mathematics::LineInfoClass::CreateLineInfo(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end) {
    //----- À•W“o˜^
    m_lineInfo.startPos = start;
    m_lineInfo.endPos   = end;
    return Mathematics::LineInfo();

    //----- •ûŒü“o˜^
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.startPos), Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.endPos));
}
