#ifndef ____STAGECREATER_H___
#define ____STAGECREATER_H___

#include <DXGame/GameObject.h>
#include <DXGame/Obstacles.h>
#include <list>


class StageCreaterControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;

    // ��Q���𐶐�����
    void CreateObstacles(void);

private:
    std::vector<GameObject*> m_block;       // �u���b�N�ւ̃A�N�Z�X��ێ�
    std::vector<Obstacles*>  m_obstacles;   // ��Q���ւ̃A�N�Z�X��ێ�
    float                    m_moveSpeed;   // �v���C���[���ǂꂾ���ړ����Ă��邩
    unsigned int             m_moveCount;   // �u���b�N�̈ړ������̃J�E���^�[
    unsigned int             m_lastIndex;   // �Ō�Ɍ��Ɉړ������u���b�N�̃C���f�b�N�X
    int                      m_obstaclesFlame;      // ��Q���̐����Ԋu
    Transform                m_firstPlayerTrans;    // �v���C���[�̏����ʒu
};


class StageCreater : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____STAGECREATER_H___
