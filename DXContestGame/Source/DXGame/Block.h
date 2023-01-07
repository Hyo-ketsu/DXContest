#ifndef ____BLOCK_H____
#define ____BLOCK_H____

#include <DXGame/GameObject.h>


class Block : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____BLOCK_H____
