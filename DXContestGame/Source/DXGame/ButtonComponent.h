#ifndef ____BUTTONCOMPONENT_H____
#define ____BUTTONCOMPONENT_H____

#include <DXGame/GameObject.h>
#include <DXGame/Component.h>


class ButtonBase : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    // @ Arg2 : �ǂݍ��݃t�@�C����
    ButtonBase(GameObject* gameObject, const std::string& file);


    virtual void Update(void) override;


    // �{�^���p�������z�֐�
    virtual void ButtonPush(void) = 0;
};


#endif // !____BUTTONCOMPONENT_H____
