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
    void SetScore(const unsigned int in) { m_score = in; }

private:
    // コンストラクタ
    ScoreGlobalRecorder(void);


    friend class Singleton<ScoreGlobalRecorder>;

    unsigned int m_score;   // 保持スコア
};


#endif // !____SCORERECORDER_H____
