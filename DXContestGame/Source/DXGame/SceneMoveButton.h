#ifndef ____SCENEMOVEBUTTON_H____
#define ____SCENEMOVEBUTTON_H____

#include <DXGame/ButtonComponent.h>
#include <DXGame/Scene.h>
#include <DXGame/SceneLoader.h>


template <class MoveScene>
class SceneMoveButton : public ButtonBase {
public:
    using ButtonBase::ButtonBase;

    void Start(void) override {}
    void ButtonPush(void) override;
};


template <class MoveScene>
void SceneMoveButton<MoveScene>::ButtonPush(void) {
    SceneLoader::Get()->MoveScene<MoveScene>();
}


#endif // !____SCENEMOVEBUTTON_H____
