#ifndef ____COMPONENT_H____
#define ____COMPONENT_H____

#include <DXGame/ClassName.h>


class Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    Component(GameObject* gameObject);
    // �f�X�g���N�^
    virtual ~Component(void) {}


    // �A�N�e�B�u�Q�b�^�[
    const bool GetActive(void) const { return m_isActive; }
    // �A�N�e�B�u�Z�b�^�[
    void SetActive(const bool in) { m_isActive = in; }


    // �������ۃQ�b�^�[
    const bool GetInit(void) const { return m_isInit; }


    // �����Q�[���I�u�W�F�N�g�Q�b�^�[
    const GameObject* GetGameObject(void) const { return m_gameObject; }


    // ����������
    virtual void Start(void) = 0;
    // �X�V����
    virtual void Update(void) {}
    // ��X�V����
    virtual void LateUpdate(void) {}
    // �`�揈��
    virtual void Draw(void) {}

protected:
    bool        m_isActive;     // ���ݗL����
    bool        m_isInit;       // �������͂���Ă��邩
    GameObject* m_gameObject;   // ���̃R���|�[�l���g���������Ă���Q�[���I�u�W�F�N�g
};


#endif // !____COMPONENT_H____
