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

    //----- 方向登録
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(start), Utility::XMFLOAT3ToXMVECTOR(end));

    //----- 返却
    return m_lineInfo;
}


// 点から見た線の最も近い場所を計算する
DirectX::XMFLOAT3 Mathematics::PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line) {
    //----- 線の始点->線の終点への単位ベクトルを取得
    DirectX::XMVECTOR lineDirectionVec;     // 線の始点->線の終点への単位ベクトル
    lineDirectionVec = DirectX::XMVector3Normalize(line.GetLineInfo().direction);

    //----- 線の始点->点へのベクトルを取得
    DirectX::XMVECTOR lineStartToPoint;    // 線の始点->点へのベクトル
    lineStartToPoint = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos), Utility::XMFLOAT3ToXMVECTOR(point));

    //----- 線の始点->点に最も近い線上の点へのベクトルを取得
    DirectX::XMVECTOR lineStartToLineNearPoint; // 線の始点->点に最も近い線上の点へのベクトル
    lineStartToLineNearPoint = DirectX::XMVector3Dot(lineDirectionVec, lineStartToPoint);

    //----- 点の座標の計算
    DirectX::XMFLOAT3 pointPos;  // 返却用点の座標 
    DirectX::XMStoreFloat3(&pointPos, DirectX::XMVectorAdd(
        Utility::XMFLOAT3ToXMVECTOR(point), lineStartToPoint)
    );   // 線の始点 + 線の始点->点に最も近い線上の点へのベクトルで点の位置を算出する

    //----- 線の終点と点の位置の比較
    // @ Memo : 点の位置が線の終点を飛び越している場合、x,y,z どれかの要素が
    // @ Memo : 線の終点の座標の絶対値 < 点の座標の絶対値 になる。
    // @ Memo : x,y,z どれかの要素が上の式を満たしていた場合、線の終点を飛び越していると判断して線の終点の座標を使用する。
    if (fabsf(line.GetLineInfo().endPos.x) < fabsf(pointPos.x)) pointPos.x = line.GetLineInfo().endPos.x;
    if (fabsf(line.GetLineInfo().endPos.y) < fabsf(pointPos.y)) pointPos.y = line.GetLineInfo().endPos.y;
    if (fabsf(line.GetLineInfo().endPos.z) < fabsf(pointPos.z)) pointPos.z = line.GetLineInfo().endPos.z;

    return pointPos;
}
