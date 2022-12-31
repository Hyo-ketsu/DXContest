#ifndef __SAMPLER_STATE_H__
#define __SAMPLER_STATE_H__

#include <DXGame/DirectX.h>


// サンプラーステート
class SamplerState {
public:
    // コンストラクタ
	SamplerState(void);
    // デストラクタ
	~SamplerState(void);


    // サンプラーステートの作成
	const HRESULT Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address);
    // 使用
	void Bind(void);

private:
	std::unique_ptr<ID3D11SamplerState> m_state;
};

#endif // __SAMPLER_STATE_H__