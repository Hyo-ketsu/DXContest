#include <DXGame/ScoreRanking.h>
#include <DXGame/ScoreIO.h>
#include <DXGame/FilePath.h>


// ハイスコアランキングに追加する
void ScoreRanking::AddScore(const unsigned int score) {
    //----- 変数宣言
    auto it = m_score.begin();

    //----- 追加するか判定
    for (; it != m_score.end(); it++) {
        //----- その順位のスコアより追加スコアのほうが大きいか
        if (score > *it) {
            //----- 大きい。判定をやめる
            break;
        }
    }

    //----- 追加を行うか判定する
    if (it == m_score.end()) return;    // イテレータが最後に到達している。終了

    //----- 追加を行う。最後の要素に代入（降順にソートされているので最後が最小の値になるため）
    m_score.at(m_score.size() - 1) = score;

    //----- ソートする
    std::sort(m_score.begin(), m_score.end(), std::greater<unsigned int>());
}
// ハイスコアランキングを取得する
unsigned int ScoreRanking::GetScore(const unsigned int rank) const {
    //----- 返却
    return m_score.at(rank);
}


// コンストラクタ
ScoreRanking::ScoreRanking(void) {
    //----- メンバ初期化
    m_score.fill(0);
    m_scoreIO = std::make_unique<std::remove_reference_t<decltype(*m_scoreIO.get())>>();
    m_scoreIO->SetFilePath(FilePath::SCOREDATA_PATH + SCORE_RANKING_FILE_NAME);

    //----- スコア読み込み
    m_score = m_scoreIO->ReadScore();
}
// デストラクタ
ScoreRanking::~ScoreRanking(void) {
    //----- スコア保存
    m_scoreIO->WriteScore(m_score);
}
