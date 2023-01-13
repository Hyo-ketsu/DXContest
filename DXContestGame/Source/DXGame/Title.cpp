#include <DXGame/Title.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneMoveButton.h>
#include <DXGame/Stage1.h>
#include <DXGame/MenuMoveScene.h>
#include <DXGame/MenuButtonSelector.h>
#include <DXGame/SpriteComponent.h>
#include <DXGame/Result.h>
#include <DXGame/HighScore.h>


void Title::InitScene(void) {
    //----- タイトル作成
    auto* title       = this->CreatePrefab<GameObject>(Transform({ 0,0.1f,0 }, { 0.4f,0.2f,1.0f }));
    auto* titleSprite = new SpriteShowComponent(title, LOAD_TITLE_FILENAME);
    title->AddComponent(titleSprite);

    //----- ボタン生成
    // ゲーム開始ボタン
    auto* moveGame       = this->CreatePrefab<GameObject>(Transform({ 0,-0.2f,0 }, SIZE_BUTTON));
    auto* moveGameSprite = new SpriteShowComponent(moveGame, LOAD_GAME_BUTTON_FILENAME);
    auto* moveGameComp   = new MenuMoveSceneComponent<Stage1>(moveGame);
    moveGame->AddComponent(moveGameSprite);
    moveGame->AddComponent(moveGameComp);
    // ハイスコア表示ボタン
    auto* moveHighScore       = this->CreatePrefab<GameObject>(Transform({ 0,-0.475f,0 }, SIZE_BUTTON));
    auto* moveHighScoreSprite = new SpriteShowComponent(moveHighScore, LOAD_HIGHSCORE_BUTTON_FILENAME);
    auto* moveHighScoreComp   = new MenuMoveSceneComponent<HighScore>(moveHighScore);
    moveHighScore->AddComponent(moveHighScoreSprite);
    moveHighScore->AddComponent(moveHighScoreComp);

    //----- メニュー生成
    this->CreatePrefab<MenuGameObject>();
}
