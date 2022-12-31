#ifndef ____COLLSION_H____
#define ____COLLSION_H____

#include "Geometory.h"


class Collision {
public:
    //----- �����蔻����s���`��
    struct Plane {
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT3 pos;
    };

    //----- �����蔻����s���`��
    struct Triangle {
        DirectX::XMFLOAT3 p[3]; // �O�p�`�̍��W
    };

    struct Ray {
        DirectX::XMFLOAT3 start;
        DirectX::XMFLOAT3 direction;
        float length;
    };

    //----- �����蔻��̌���
    struct Result {
        bool hit;
        DirectX::XMFLOAT3 point;
    };

public:
    //----- �`�󂲂Ƃ̓����蔻�������
    static Result CheckRayPlane(Ray ray, Plane plane);

    //----- �`�󂲂Ƃ̓����蔻�������
    static Result CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle);
};


#endif // !____COLLSION_H____
