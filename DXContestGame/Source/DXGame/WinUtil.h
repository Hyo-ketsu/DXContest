#ifndef __WIN_UTIL_H__
#define __WIN_UTIL_H__


//----- 定義
enum AppState
{
	APP_STATE_MESSAGE,
	APP_STATE_WAIT,
	APP_STATE_QUIT
};

//----- プロトタイプ宣言
HRESULT InitWindow(LPCSTR appName, LONG width, LONG height);
void    UninitWindow(void);
AppState UpdateWindow(void);
HWND GetHWND(void);
void Error(const char* mes);

#endif // __WIN_UTIL_H__