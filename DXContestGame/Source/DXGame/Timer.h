#ifndef __TIMER_H__
#define __TIMER_H__

#include <DXGame/Singleton.h>


// ここで時間を管理するクラス
class Timer {
public:
    // コンストラクタ
    Timer(void);
    // デストラクタ
    ~Timer(void);


    // 現在時間ゲッター
    const unsigned int& GetTime(void) const { return m_time; }


    // 初期化
    static void InitTime(void);
    // 更新
    static void UpdateTime(void);
    // 終了
    static void UninitTime(void);


    // 60FPS制御
    // @ Ret  : 更新可能か
    const bool IsFpsCheck(void);


    // 前回実行時からの経過時間
    // @ Ret  : 経過時間
    const float DeltaTime(void);

private:
    unsigned int m_time;    // 現在時間
    unsigned int m_fpsTime; // FPSチェック用
    static std::unique_ptr<unsigned int> ms_globalTime; // 全体時間
};




//--- 型宣言
using Frame = unsigned short;
using Time  = float;

//--- プロトタイプ宣言
void InitTimer(Frame fps);
void UninitTimer(void);
bool UpdateTimer(void);


void  SetFPS(Frame fps);
Frame GetFPS(void);


Time GetDeltaTime(void);


Time  ConvertFrameToTime(Frame frame);
Frame ConvertTimeToFrame(Time time);

#endif // __TIMER_H__