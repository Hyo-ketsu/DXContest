#include <DXGame/Utility.h>


// 文字列を結合する
const std::string Utility::MergeString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


// 度数（゜）をラジアンに変換する式
const float Utility::GetRad(const float rad) {
    return rad * 3.14f / 180;
}
