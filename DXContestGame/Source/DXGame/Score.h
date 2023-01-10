#ifndef ____SCORE_H____
#define ____SCORE_H____

#include <DXGame/GameObject.h>


class Score : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____SCORE_H____
