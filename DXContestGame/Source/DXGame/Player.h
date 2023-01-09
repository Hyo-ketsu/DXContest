#ifndef ____PLAYER_H____
#define ____PLAYER_H____

#include <DXGame/GameObject.h>
#include <DXGame/Singleton.h>
#include <DXGame/Polyline.h>
#include <DXGame/Singleton.h>


// プレイヤーの速度管理
class PlayerSpeedManager : public Singleton<PlayerSpeedManager> {
public:
    // デストラクタ
    ~PlayerSpeedManager(void) {}


    // 速度ゲッター
    const float GetSpeed(void) const { return m_speed; }
    // 速度セッター
    void SetSpeed(const float in) { m_speed = in; }

private:
    // コンストラクタ
    PlayerSpeedManager(void) : m_speed(0) {}


    // フレンド宣言
    friend class Singleton<PlayerSpeedManager>;

    float m_speed;  // 速度
};


class PlayerControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;
    void Collsion(void) override;
    void Draw(void) override;


private:
    float m_moveSpeed;  // プレイヤーの前進速度
    std::unique_ptr<GeometoryPolyline> m_polyline;  // Polyline
};


class Player : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____PLAYER_H____
