#ifndef ____PLAYER_H____
#define ____PLAYER_H____

#include <DXGame/GameObject.h>
#include <DXGame/Singleton.h>
#include <DXGame/Polyline.h>
#include <DXGame/Singleton.h>


// �v���C���[�̑��x�Ǘ�
class PlayerSpeedManager : public Singleton<PlayerSpeedManager> {
public:
    // �f�X�g���N�^
    ~PlayerSpeedManager(void) {}


    // ���x�Q�b�^�[
    const float GetSpeed(void) const { return m_speed; }
    // ���x�Z�b�^�[
    void SetSpeed(const float in) { m_speed = in; }

private:
    // �R���X�g���N�^
    PlayerSpeedManager(void) : m_speed(0) {}


    // �t�����h�錾
    friend class Singleton<PlayerSpeedManager>;

    float m_speed;  // ���x
};


class PlayerControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;
    void Collsion(void) override;
    void Draw(void) override;


private:
    float m_moveSpeed;  // �v���C���[�̑O�i���x
    std::unique_ptr<GeometoryPolyline> m_polyline;  // Polyline
};


class Player : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____PLAYER_H____
