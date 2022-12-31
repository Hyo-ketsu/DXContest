#ifndef ____COLLSION_H____
#define ____COLLSION_H____

#include "Geometory.h"


class Collision {
public:
    //----- 当たり判定を行う形状
    struct Plane {
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT3 pos;
    };

    //----- 当たり判定を行う形状
    struct Triangle {
        DirectX::XMFLOAT3 p[3]; // 三角形の座標
    };

    struct Ray {
        DirectX::XMFLOAT3 start;
        DirectX::XMFLOAT3 direction;
        float length;
    };

    //----- 当たり判定の結果
    struct Result {
        bool hit;
        DirectX::XMFLOAT3 point;
    };

public:
    //----- 形状ごとの当たり判定を実装
    static Result CheckRayPlane(Ray ray, Plane plane);

    //----- 形状ごとの当たり判定を実装
    static Result CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle);
};


#endif // !____COLLSION_H____
