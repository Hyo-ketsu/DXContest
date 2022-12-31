#include <DXGame/SamplerState.h>


// コンストラクタ
SamplerState::SamplerState(void)
	: m_state(nullptr) {
}
// デストラクタ
SamplerState::~SamplerState(void) {
	if (m_state) {
		m_state->Release();
	}
}


// サンプラーステートの作成
const HRESULT SamplerState::Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address) {
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter   = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
    auto sampleState = m_state.get();
	return GetDevice()->CreateSamplerState(&desc, &sampleState);
}
// 使用
void SamplerState::Bind(void) {
    auto sampleState = m_state.get();
	GetContext()->PSSetSamplers(0, 1, &sampleState);
}