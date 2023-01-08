#ifndef ____HP_H____
#define ____HP_H____

#include <DXGame/Component.h>


// HP�R���|�[�l���g
class HP : public Component {
public:
    using Component::Component;

    void Start(void) override {}


    // �̗̓Q�b�^�[
    const int GetHP(void) const { return m_hp; }
    // �̗̓Z�b�^�[
    void SetHP(const int in) { m_hp = in; }


    // �_���[�W��^����
    // @ Arg1 : �_���[�W�l�i���l�ŉ񕜁j
    void Damage(const int damage);


    // ��������
    // @ Ret  : ����ł��邩
    const bool IsDead(void) const;


private:
    int m_hp = 1;
};


#endif // !____HP_H____
