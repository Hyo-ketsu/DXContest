#include <DXGame/SamplerState.h>


// �R���X�g���N�^
SamplerState::SamplerState(void)
	: m_state(nullptr) {
}
// �f�X�g���N�^
SamplerState::~SamplerState(void) {
	if (m_state) {
		m_state->Release();
	}
}


// �T���v���[�X�e�[�g�̍쐬
const HRESULT SamplerState::Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address) {
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter   = filter;
	desc.AddressU = address;
	desc.AddressV = address;
	desc.AddressW = address;
    auto sampleState = m_state.get();
	return GetDevice()->CreateSamplerState(&desc, &sampleState);
}
// �g�p
void SamplerState::Bind(void) {
    auto sampleState = m_state.get();
	GetContext()->PSSetSamplers(0, 1, &sampleState);
}