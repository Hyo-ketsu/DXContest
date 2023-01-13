#ifndef ____MENUBUTTONSELECTOR_H____
#define ____MENUBUTTONSELECTOR_H____

#include <DXGame/Component.h>
#include <DXGame/GameObject.h>


// MenuGameObject�p�̃R���|�[�l���g
class MenuGameObjectClient : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override {}


    // MenuGameObject�őI�����ꂽ�ۂɍs���A�N�V����
    virtual void Action(void) = 0;
};


// �^�C�g���Ȃǂ̕����I���ł����ʂ̃{�^�����܂Ƃ߂�R���|�[�l���g
class MenuGameObjectControl : public Component{
public:
    using Component::Component;


    void Start(void) override;
    void Update(void) override;


    // �Q�[���I�u�W�F�N�g��ǉ�����
    // @ Memo : �ǉ�����Q�[���I�u�W�F�N�g�� MenuGameObjectClient ��ێ����Ă��Ȃ���Η�O�𓊂��܂�
    // @ Arg1 : �Q�[���I�u�W�F�N�g
    void AddGameObject(GameObject *gameObject);

private:
    std::vector<GameObject*> m_children;        // ���j���[�őI������I�u�W�F�N�g
    unsigned int             m_currentCursor;   // �J�[�\���ʒu
};


// MenuGameObjectControl��ێ����Ă���Q�[���I�u�W�F�N�g
class MenuGameObject : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____MENUBUTTONSELECTOR_H____
