#ifndef __TIMER_H__
#define __TIMER_H__

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