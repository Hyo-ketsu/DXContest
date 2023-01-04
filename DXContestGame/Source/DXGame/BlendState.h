#ifndef __BLEND_STATE_H__
#define __BLEND_STATE_H__

#include <DXGame/DirectX.h>


// ブレンドステート
class BlendState {
public:
    // コンストラクタ
	BlendState(void);
    // デストラクタ
	~BlendState(void);


    // ブレンドステートの作成
    // @ Ret  : 成功したか
    // @ Arg1 : 作成用の初期化設定
	HRESULT Create(const D3D11_RENDER_TARGET_BLEND_DESC desc);


    // ブレンドステートを使用する
	void Bind(void);

private:
	std::unique_ptr<ID3D11BlendState> m_blendState;  // ブレンドステートの保持
};

#endif // __BLEND_STATE_H__