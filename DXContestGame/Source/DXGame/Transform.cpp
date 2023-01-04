#include <DXGame/Transform.h>

// コンストラクタ
Transform::Transform(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& angle)
    : pos(pos)
    , size(size)
    , angle(angle) {
}


const Transform& Transform::operator=(const Transform& r) {
    this->pos   = r.pos;
    this->size  = r.size;
    this->angle = r.angle;
    return *this;
}
