#ifndef ____BUTTONCOMPONENT_H____
#define ____BUTTONCOMPONENT_H____

#include <DXGame/GameObject.h>
#include <DXGame/Component.h>


class ButtonBase : public Component {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    // @ Arg2 : 読み込みファイル名
    ButtonBase(GameObject* gameObject, const std::string& file);


    virtual void Update(void) override;


    // ボタン用純粋仮想関数
    virtual void ButtonPush(void) = 0;
};


#endif // !____BUTTONCOMPONENT_H____
