#ifndef __BLEND_STATE_H__
#define __BLEND_STATE_H__

#include <DXGame/DirectX.h>


// �u�����h�X�e�[�g
class BlendState {
public:
    // �R���X�g���N�^
	BlendState(void);
    // �f�X�g���N�^
	~BlendState(void);


    // �u�����h�X�e�[�g�̍쐬
    // @ Ret  : ����������
    // @ Arg1 : �쐬�p�̏������ݒ�
	HRESULT Create(const D3D11_RENDER_TARGET_BLEND_DESC desc);


    // �u�����h�X�e�[�g���g�p����
	void Bind(void);

private:
	std::unique_ptr<ID3D11BlendState> m_blendState;  // �u�����h�X�e�[�g�̕ێ�
};

#endif // __BLEND_STATE_H__