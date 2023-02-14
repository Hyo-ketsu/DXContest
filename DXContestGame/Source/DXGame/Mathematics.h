#ifndef ____MATHEMATICS_H____
#define ____MATHEMATICS_H____


// 自作数学関数
namespace Mathematics {
    // 線情報
    struct LineInfo {
        DirectX::XMFLOAT3 startPos;     // 始点
        DirectX::XMFLOAT3 endPos;       // 終点
        DirectX::XMVECTOR direction;    // 線の向きのベクトル
    };


    // 始点と終点を設定することで線の情報を生成するクラス
    class LineInfoClass {
    public:
        // コンストラクタ
        // @ Arg1 : 始点
        // @ Arg2 : 終点
        LineInfoClass(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end);


        // 線情報ゲッター
        LineInfo GetLineInfo(void) const { return m_lineInfo; }


        // 線情報を登録する
        // @ Ret  : 線情報
        // @ Arg1 : 始点
        // @ Arg2 : 終点
        LineInfo CreateLineInfo(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end);

    private:
        LineInfo m_lineInfo;    // 線の情報
    };
}


// 自作数学関数
namespace Mathematics { 
    // 点から見た線の最も近い場所を計算する
    // @ Ret  : 座標
    // @ Arg1 : 点の座標
    // @ Arg2 : 線の情報
    DirectX::XMFLOAT3 PointToLineNear(const DirectX::XMFLOAT3& point, const Mathematics::LineInfoClass& line);
}


#endif // !____MATHEMATICS_H____
