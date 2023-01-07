#ifndef ____PLAYER_H____
#define ____PLAYER_H____

#include <DXGame/GameObject.h>


class PlayerControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;


    // 体力ゲッター


private:
    int m_hp;   // 現在体力

};


class Player : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____PLAYER_H____
