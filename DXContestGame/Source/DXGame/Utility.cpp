#include <DXGame/Utility.h>


// ���������������
const std::string Utility::MergeString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


// �x���i�K�j�����W�A���ɕϊ����鎮
const float Utility::GetRad(const float rad) {
    return rad * 3.14f / 180;
}
