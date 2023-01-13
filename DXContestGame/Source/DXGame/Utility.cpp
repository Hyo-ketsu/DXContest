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
