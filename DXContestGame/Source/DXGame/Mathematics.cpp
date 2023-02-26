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
    m_lineInfo.direction = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(end), Utility::XMFLOAT3ToXMVECTOR(start));

    //----- 返却
    return m_lineInfo;
}


// 点から見た線の最も近い場所を計算する
DirectX::XMFLOAT3 Mathematics::PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line) {
    //----- 線の方向が {0,0,0} だったら（線ではなく点になってたら）線の始点を返却
    if (DirectX::XMVector3Equal(line.GetLineInfo().direction, DirectX::XMVectorZero())) {
        //----- 線の始点を返却
        return line.GetLineInfo().startPos;
    }

    //----- 線の始点->線の終点への単位ベクトルを取得
    DirectX::XMVECTOR lineDirectionVec;     // 線のv始点->線の終点への単位ベクトル
    lineDirectionVec = DirectX::XMVector3Normalize(line.GetLineInfo().direction);

    //----- 線の始点->点へのベクトルを取得
    DirectX::XMVECTOR lineStartToPoint;    // 線の始点->点へのベクトル
    lineStartToPoint = DirectX::XMVectorSubtract(Utility::XMFLOAT3ToXMVECTOR(point), Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos));

    //----- 線の始点->点に最も近い線上の点へのベクトルを取得
    DirectX::XMVECTOR lineStartToLineNearPoint; // 線の始点->点に最も近い線上の点へのベクトル
    for (int i = 0; i < 3; i++) {   // 各軸内積
        lineStartToLineNearPoint.m128_f32[i] = lineDirectionVec.m128_f32[i] * lineStartToPoint.m128_f32[i];
    }
    lineStartToLineNearPoint.m128_f32[3] = 0.f;

    //----- 点の座標の計算
    DirectX::XMFLOAT3 pointPos;  // 返却用点の座標 
    DirectX::XMStoreFloat3(&pointPos, DirectX::XMVectorSubtract(
        Utility::XMFLOAT3ToXMVECTOR(line.GetLineInfo().startPos), lineStartToLineNearPoint)
    );   // 線の始点 + 線の始点->点に最も近い線上の点へのベクトルで点の位置を算出する

    //----- 線内に収める
    do {
        //----- Usingディレクティブ
        using namespace Utility;

        //----- 変数宣言
        bool isFas = false; // 対称点より遠いか

        //----- 距離を計算
        // @ Memo : 浮動小数誤差が気になる
        isFas |= XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, line.GetLineInfo().endPos)) <
                 XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, pointPos));    // 始点からの距離計算
        isFas |= XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos, line.GetLineInfo().startPos)) <
                 XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos, pointPos));      // 終点からの距離計算
        if (isFas == false) break;  // 線内。判定を終了する

        //----- 始点・終点座標代入
        if (XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().startPos, pointPos)) <
            XMFLOAT3Length(XMFLOAT3Subtract(line.GetLineInfo().endPos,   pointPos))   ) {
            //----- 始点のほうが近い。始点座標代入
            pointPos = line.GetLineInfo().startPos;
        }
        else {
            //----- 終点のほうが近い。終点座標代入
            pointPos = line.GetLineInfo().endPos;
        }
    } while (false);

    //----- 返却
    return pointPos;
}
