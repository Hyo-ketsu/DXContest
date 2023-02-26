#ifndef ____UTILITY_H____
#define ____UTILITY_H____


namespace Utility {
    // 文字列を結合する
    // @ Ret  : 結合後の文字列
    // @ Arg1 : 文字列
    // @ Arg2 : 文字列
    const std::string MergeString(const std::string& string1, const std::string& string2);


    // float変数 と float変数が等価かどうか判定する
    // @ Ret  : 等価か
    // @ Arg1 : float変数
    // @ Arg2 : float変数（デフォルト：0.f）
    const bool FloatComparison(const float float1, const float float2 = 0.f);


    // 度数（゜）をラジアンに変換する式
    const float GetRad(const float rad);


    // XMFLOAT3をXMVECTORに変換する関数
    DirectX::XMVECTOR XMFLOAT3ToXMVECTOR(const DirectX::XMFLOAT3& xmfloat3);


    // FLOAT3の減算を行う
    // @ Ret  : 差
    // @ Arg1 : 減算される値
    // @ Arg1 : 減算する値
    const DirectX::XMFLOAT3 XMFLOAT3Subtract(const DirectX::XMFLOAT3& xmfloat1, const DirectX::XMFLOAT3& xmfloat2);


    // FLOAT3の長さを計算します
    // @ Memo : 各要素の絶対値の合計です
    // @ Ret  : 長さ
    // @ Arg1 : 長さを計算するデータ
    const float XMFLOAT3Length(const DirectX::XMFLOAT3& xmfloat);
}


#endif // !____UTILITY_H____
