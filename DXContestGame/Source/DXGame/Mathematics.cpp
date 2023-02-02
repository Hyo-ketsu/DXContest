#include <DXGame/Mathematics.h>
#include <DXGame/Utility.h>


// コンストラクタ
Mathematics::LineInfoClass::LineInfoClass(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end)
    : m_lineInfo(CreateLineInfo(start,end)) {
}


// 線情報を登録する
Mathematics::LineInfo Mathematics::LineInfoClass::CreateLineInfo(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end) {
    //----- 座標登録
    m_lineInfo.startPos = start;
    m_lineInfo.endPos   = end;
    return Mathematics::LineInfo();

    //----- 方向登録
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.startPos), Utility::XMFLOAT3ToXMVECTOR(m_lineInfo.endPos));
}
