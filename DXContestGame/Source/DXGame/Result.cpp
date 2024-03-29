#include <DXGame/Result.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneMoveButton.h>
#include <DXGame/Title.h>
#include <DXGame/Number.h>
#include <DXGame/ScoreRecorder.h>


void Result::InitScene(void) {
    //----- ボタン生成
    auto* button = this->CreatePrefab<GameObject>(Transform({ 0,-0.2f,0 }, SIZE_BUTTON));
    auto* buttonComp = new SceneMoveButton<Title>(button, LOAD_TITLE_BUTTON_FILENAME);
    button->AddComponent(buttonComp);

    //----- スコア表示
    auto* score = this->CreatePrefab<GameObject>(Transform(DirectX::XMFLOAT3(-0.25, 0, 0), DirectX::XMFLOAT3(0.1f, 0.1f, -1)));
    auto* scoreCompo = score->AddComponent<NumberShow>();
    scoreCompo->SetNumber(ScoreGlobalRecorder::Get()->GetScore());

    //----- ハイスコアランキング登録
    ScoreGlobalRecorder::Get()->AddHighScoreRanking();
}
