#ifndef ____COLLSIONSYSTEM_H____
#define ____COLLSIONSYSTEM_H____

#include <DXGame/Singleton.h>
#include <DXGame/Collsion.h>


// �Փ˔�����s���N���X
class CollsionSystem : public Singleton<CollsionSystem> {
public:
    // �f�X�g���N�^
    ~CollsionSystem(void) override {}


    // �����蔻��̒ǉ�
    // @ Arg1 : �ǉ����铖���蔻��
    void AddCollsion(Collsion* collsion);
    // �����蔻��̍폜
    // @ Arg1 : �폜���铖���蔻��
    void DeleteCollsion(Collsion* collsion);


    // �S�Ă̓����蔻��𔻒肷��
    void AllCollsionHit(void);
private:
    // �R���X�g���N�^
    CollsionSystem(void) {}


    // friend�N���X�錾
    friend class Singleton<CollsionSystem>;

    std::vector<Collsion*> m_collsion;  // �����蔻��̕ێ�
};


#endif // !____COLLSIONSYSTEM_H____
