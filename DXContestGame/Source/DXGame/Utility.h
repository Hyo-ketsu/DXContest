#ifndef ____UTILITY_H____
#define ____UTILITY_H____


namespace Utility {
    // 文字列を結合する
    // @ Ret  : 結合後の文字列
    // @ Arg1 : 文字列
    // @ Arg2 : 文字列
    const std::string MergeString(const std::string& string1, const std::string& string2);


    // 度数（゜）をラジアンに変換する式
    const float GetRad(const float rad);
}


#endif // !____UTILITY_H____
