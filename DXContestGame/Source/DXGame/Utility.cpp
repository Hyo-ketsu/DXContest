#include <DXGame/Utility.h>


// •¶š—ñ‚ğŒ‹‡‚·‚é
const std::string Utility::MergeString(const std::string& string1, const std::string& string2) {
    return string1 + string2;
}


// float•Ï” ‚Æ float•Ï”‚ª“™‰¿‚©‚Ç‚¤‚©”»’è‚·‚é
const bool Utility::FloatComparison(const float float1, const float float2) {
    return fabsf(float1 - float2) <= FLT_EPSILON ? true : false;
}


// “x”iKj‚ğƒ‰ƒWƒAƒ“‚É•ÏŠ·‚·‚é®
const float Utility::GetRad(const float rad) {
    return rad * 3.14f / 180;
}


// XMFLOAT3‚ğXMVECTOR‚É•ÏŠ·‚·‚éŠÖ”
DirectX::XMVECTOR Utility::XMFLOAT3ToXMVECTOR(const DirectX::XMFLOAT3& xmfloat3) {
    return DirectX::XMLoadFloat3(&xmfloat3);
}


// FLOAT3‚ÌŒ¸Z‚ğs‚¤
const DirectX::XMFLOAT3 Utility::XMFLOAT3Subtract(const DirectX::XMFLOAT3& xmfloat1, const DirectX::XMFLOAT3& xmfloat2) {
    //----- •Ï”éŒ¾
    DirectX::XMFLOAT3 ret;
    
    //----- Še—v‘fŒvZ
    ret.x = xmfloat1.x - xmfloat2.x;
    ret.y = xmfloat1.y - xmfloat2.y;
    ret.z = xmfloat1.z - xmfloat2.z;

    //----- •Ô‹p
    return ret;
}


// FLOAT3‚Ì’·‚³‚ğŒvZ‚µ‚Ü‚·
const float Utility::XMFLOAT3Length(const DirectX::XMFLOAT3& xmfloat) {
    return fabsf(xmfloat.x) + fabsf(xmfloat.y) + fabsf(xmfloat.z);
}