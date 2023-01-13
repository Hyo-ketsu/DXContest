#include <DXGame/ScoreRecorder.h>


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
        m_highScore = m_score;
    }
}
