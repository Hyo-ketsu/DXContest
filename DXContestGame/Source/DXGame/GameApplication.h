#ifndef ____GAMEAPPLICATION_H____
#define ____GAMEAPPLICATION_H____

#include <DXGame/Singleton.h>


// ゲームの終了などのゲーム全体の管理をするクラス
class GameApplication : public Singleton<GameApplication> {
public:
    // ゲーム終了ゲッター
    const bool GetGameEnd(void) const { return m_isGameEnd; }
    // ゲーム終了セッター
    void SetGameEnd(const bool in) { m_isGameEnd = in; }


private:
    // コンストラクタ
    GameApplication(void);


    // フレンド宣言
    friend class Singleton<GameApplication>;

    bool m_isGameEnd;   // ゲームが終了したか
};


#endif // !____GAMEAPPLICATION_H____
