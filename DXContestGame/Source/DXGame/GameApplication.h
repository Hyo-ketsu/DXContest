#ifndef ____GAMEAPPLICATION_H____
#define ____GAMEAPPLICATION_H____

#include <DXGame/Singleton.h>


// ゲームの終了などのゲーム全体の管理をするクラス
class GameApplication : public Singleton<GameApplication> {
public:
    // デストラクタ
    ~GameApplication(void) override;


    // ゲーム終了ゲッター
    const bool GetGameEnd(void) const { return m_isGameEnd; }
    // ゲーム終了セッター
    void SetGameEnd(const bool in) { m_isGameEnd = in; }


    // ウィンドウ横サイズゲッター
    const unsigned int GetWindowSizeX(void) const { return m_windowSizeX; }
    // ウィンドウ横サイズセッター
    void SetWindowSizeX(const unsigned int in) { m_windowSizeX = in; }
    // ウィンドウ縦サイズゲッター
    const unsigned int GetWindowSizeY(void) const { return m_windowSizeY; }
    // ウィンドウ縦サイズセッター
    void SetWindowSizeY(const unsigned int in) { m_windowSizeY = in; }


    // マウスカーソル座標ゲッター
    const DirectX::XMINT2 GetMouseTransform(void) const { return m_mouseTrasform; }
    // マウスカーソル座標セッター
    void SetMouseTransform(const DirectX::XMINT2& in); 


private:
    // コンストラクタ
    GameApplication(void);


    // フレンド宣言
    friend class Singleton<GameApplication>;

    bool m_isGameEnd;   // ゲームが終了したか
    unsigned int m_windowSizeX;      // ウィンドウの横サイズ
    unsigned int m_windowSizeY;      // ウィンドウの縦サイズ
    DirectX::XMINT2 m_mouseTrasform; // マウスカーソルの現在位置
};


#endif // !____GAMEAPPLICATION_H____
