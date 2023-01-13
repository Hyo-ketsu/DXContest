#ifndef ____SCORERECORDER_H____
#define ____SCORERECORDER_H____

#include <DXGame/GameObject.h>
#include <DXGame/Singleton.h>


// スコアを保持する
class ScoreGlobalRecorder : public Singleton<ScoreGlobalRecorder> {
public:
    // デストラクタ
    ~ScoreGlobalRecorder(void) override;


    // 現スコアゲッター
    const unsigned int GetScore(void) const { return m_score; }
    // 現スコアセッター
    void SetScore(const unsigned int in); 


    // ハイスコアゲッター
    const unsigned int GetHighScore(void) const { return m_highScore; }

private:
    // コンストラクタ
    ScoreGlobalRecorder(void);


    friend class Singleton<ScoreGlobalRecorder>;

    unsigned int m_score;       // 保持スコア
    unsigned int m_highScore;   // 保持ハイスコア
};


#endif // !____SCORERECORDER_H____
