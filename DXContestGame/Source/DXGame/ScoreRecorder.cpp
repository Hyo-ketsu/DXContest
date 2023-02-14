#include <DXGame/ScoreRecorder.h>
#include <DXGame/ScoreIO.h>
#include <DXGame/FilePath.h>


// コンストラクタ
ScoreGlobalRecorder::ScoreGlobalRecorder(void)
    : m_score(0) 
    , m_highScore(0) {
}


// デストラクタ
ScoreGlobalRecorder::~ScoreGlobalRecorder(void) {
}


// 現スコアセッター
void ScoreGlobalRecorder::SetScore(const unsigned int in) {
    //----- 現スコア更新
    m_score = in; 

    //----- ハイスコア更新
    if (m_highScore < m_score) {
        //----- 保持しているハイスコア更新
        m_highScore = m_score;
    }
}


// ハイスコアをランキングに登録する
void ScoreGlobalRecorder::AddHighScoreRanking(void) const {
    //----- ランキングの更新
    ScoreRanking::Get()->AddScore(m_highScore);
}
