#ifndef ____OBSTACLES_H____
#define ____OBSTACLES_H____

#include <DXGame/GameObject.h>


class Obstacles : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____OBSTACLES_H____
