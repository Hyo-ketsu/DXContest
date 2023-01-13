#ifndef ____MENUMOVESCENE_H____
#define  ____MENUMOVESCENE_H____

#include <DXGame/MenuButtonSelector.h>
#include <DXGame/SceneLoader.h>


// メニュークライアントを継承してシーンを移動するコンポーネント
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
