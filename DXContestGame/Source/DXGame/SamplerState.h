#ifndef __SAMPLER_STATE_H__
#define __SAMPLER_STATE_H__

#include <DXGame/DirectX.h>


// �T���v���[�X�e�[�g
class SamplerState {
public:
    // �R���X�g���N�^
	SamplerState(void);
    // �f�X�g���N�^
	~SamplerState(void);


    // �T���v���[�X�e�[�g�̍쐬
	const HRESULT Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address);
    // �g�p
	void Bind(void);

private:
	std::unique_ptr<ID3D11SamplerState> m_state;
};

#endif // __SAMPLER_STATE_H__