#ifndef __DIRECTX_H__
#define __DIRECTX_H__


// Deviceを取得する
// @ Ret  : Device
ID3D11Device* GetDevice(void);
// Contextを取得する
// @ Ret  ; Context
ID3D11DeviceContext* GetContext(void);
// SwapChainを取得する
// @ Ret  : SwapChain
IDXGISwapChain* GetSwapChain(void);


// DirectXを初期化する
// @ Ret  : 成功したか
// @ Arg1 : ウィンドウハンドル
// @ Arg2 : ウィンドウ横サイズ
// @ Arg3 : ウィンドウ縦サイズ
// @ Arg4 : フルスクリーンか
const HRESULT InitDX(HWND hWnd, const UINT width, const UINT height, const bool isFullscreen);


// DirectXを終了する
void UninitDX(void);


// 描画前処理
void BeginDrawDX(void);
// 描画後処理
void EndDrawDX(void);


// 深度バッファを有効にするか
void EnableDepth(const bool isEnable);

#endif // __DIRECTX_H__