#include <DXGame/HighScore.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneMoveButton.h>
#include <DXGame/Title.h>
#include <DXGame/Number.h>
#include <DXGame/ScoreRecorder.h>
#include <DXGame/ScoreRanking.h>


const float SCORE_SIZE = 0.1f;  // スコア表示オブジェクトのサイズ


void HighScore::InitScene(void) {
    //----- ボタン生成
    auto* button = this->CreatePrefab<GameObject>(Transform({ 0,-0.2f,0 }, SIZE_BUTTON));
    auto* buttonComp = new SceneMoveButton<Title>(button, LOAD_TITLE_BUTTON_FILENAME);
    button->AddComponent(buttonComp);

    //----- スコア表示
    for (int i = 0; i < SCORE_RANKING; i++) {
        auto* score = this->CreatePrefab<GameObject>(Transform(DirectX::XMFLOAT3(-0.25, SCORE_SIZE * (SCORE_RANKING - 1 - i), 0), DirectX::XMFLOAT3(SCORE_SIZE, SCORE_SIZE, -1)));
        auto* scoreCompo = score->AddComponent<NumberShow>();
        scoreCompo->SetNumber(ScoreRanking::Get()->GetScore(i));
    }
}
