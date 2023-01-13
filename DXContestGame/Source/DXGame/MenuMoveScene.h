#ifndef ____MENUMOVESCENE_H____
#define  ____MENUMOVESCENE_H____

#include <DXGame/MenuButtonSelector.h>
#include <DXGame/SceneLoader.h>


// ���j���[�N���C�A���g���p�����ăV�[�����ړ�����R���|�[�l���g
template <class MoveScene>
class MenuMoveSceneComponent : public MenuGameObjectClient {
public:
    using MenuGameObjectClient::MenuGameObjectClient;

    
    void Action(void) override;
};


template <class MoveScene>
void MenuMoveSceneComponent<MoveScene>::Action(void) {
    SceneLoader::Get()->MoveScene<MoveScene>();
}


#endif // !____MENUMOVESCENE_H____
