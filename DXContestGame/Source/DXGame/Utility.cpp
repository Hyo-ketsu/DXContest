#include <DXGame/Utility.h>


// 文字列を結合する
const std::string Utility::MergeString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


// float変数 と float変数が等価かどうか判定する
const bool Utility::FloatComparison(const float float1, const float float2) {
    return fabsf(float1 - float2) <= FLT_EPSILON ? true : false;
}


// 度数（゜）をラジアンに変換する式
const float Utility::GetRad(const float rad) {
    return rad * 3.14f / 180;
}


// XMFLOAT3をXMVECTORに変換する関数
DirectX::XMVECTOR Utility::XMFLOAT3ToXMVECTOR(const DirectX::XMFLOAT3& xmfloat3) {
    return DirectX::XMLoadFloat3(&xmfloat3);
}


// FLOAT3の減算を行う
const DirectX::XMFLOAT3 Utility::XMFLOAT3Subtract(const DirectX::XMFLOAT3& xmfloat1, const DirectX::XMFLOAT3& xmfloat2) {
    //----- 変数宣言
    DirectX::XMFLOAT3 ret;
    
    //----- 各要素計算
    ret.x = xmfloat1.x - xmfloat2.x;
    ret.y = xmfloat1.y - xmfloat2.y;
    ret.z = xmfloat1.z - xmfloat2.z;

    //----- 返却
    return ret;
}


// FLOAT3の長さを計算します
const float Utility::XMFLOAT3Length(const DirectX::XMFLOAT3& xmfloat) {
    return fabsf(xmfloat.x) + fabsf(xmfloat.y) + fabsf(xmfloat.z);
}