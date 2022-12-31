#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>


// キー入力初期化処理
// @ Ret  : 初期化に成功したか
const HRESULT InitInput(void);
// キー入力終了処理
void UninitInput(void);


// キー入力情報を取得する
void UpdateInput(void);


// 指定したキーが入力されたか
// @ Ret  : 入力されているか
// @ Arg1 : 入力キー
bool IsKeyPress(const BYTE key);
// 指定したキーが押されたか
// @ Ret  : 入力されているか
// @ Arg1 : 入力キー
bool IsKeyTrigger(const BYTE key);
// 指定したキーが離されたか
// @ Ret  : 入力されているか
// @ Arg1 : 入力キー
bool IsKeyRelease(const BYTE key);

#endif // __INPUT_H__