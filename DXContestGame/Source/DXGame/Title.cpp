#include <DXGame/Title.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneMoveButton.h>
#include <DXGame/Stage1.h>


void Title::InitScene(void) {
    //----- ボタン生成
    auto* button =  this->CreatePrefab<GameObject>(Transform({ 0,-0.2f,0 }, SIZE_BUTTON));
    auto* buttonComp = new SceneMoveButton<Stage1>(button, LOAD_GAME_BUTTON_FILENAME);
    button->AddComponent(buttonComp);
}
