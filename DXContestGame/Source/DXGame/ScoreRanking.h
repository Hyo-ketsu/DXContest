#ifndef ____SCORERANKING_H____
#define ____SCORERANKING_H____

#include <DXGame/Singleton.h>


// 前方宣言
class ScoreIO;


const unsigned int SCORE_RANKING = 3;   // ランキングに記録する順位数
const std::string  SCORE_RANKING_FILE_NAME = "ScoreRanking.csv";


using ScoreArray = std::array<unsigned int, SCORE_RANKING>; // スコアを保持する配列型


// ハイスコアランキングの点数のみ保持しておくクラス
class ScoreRanking : public Singleton<ScoreRanking> {
public:
    // デストラクタ
    ~ScoreRanking(void);


    // ハイスコアランキングに追加する
    // @ Arg1 : 登録するスコア
    void AddScore(const unsigned int score);
    // ハイスコアランキングを取得する
    // @ Memo : 範囲外（記録Ranking外）を指定した際はそのまま例外を吐きます
    // @ Ret  : 数値（その順位にスコアが存在しない場合は0を返します）
    // @ Arg1 : 取得したい順位
    unsigned int GetScore(const unsigned int rank) const;

private:
    // コンストラクタ
    ScoreRanking(void);


    friend class Singleton<ScoreRanking>;


    ScoreArray m_score;  // 各順位のスコアを集めた保存したクラス（無論降順）
    std::unique_ptr<ScoreIO> m_scoreIO; // スコア入出力用クラス
};


#endif // !____SCORERANKING_H____
