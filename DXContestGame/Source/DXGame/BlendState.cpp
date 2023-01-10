#include <DXGame/BlendState.h>


// �R���X�g���N�^
BlendState::BlendState(void)
	: m_blendState(nullptr) {
}
// �f�X�g���N�^
BlendState::~BlendState(void) {
    //----- �I������
	if (m_blendState != nullptr) {
		m_blendState->Release();
	}
}


// �u�����h�X�e�[�g�̍쐬
HRESULT BlendState::Create(const D3D11_RENDER_TARGET_BLEND_DESC desc) {
    //----- �ϐ��錾
	D3D11_BLEND_DESC  blendDesc;            // ���������
    HRESULT           ret;                  // �����ɐ�����������ԋp����

    //----- �������Ƒ��
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0] = desc;

    //----- �u�����h�X�e�[�g�쐬
    return GetDevice()->CreateBlendState(&blendDesc, &m_blendState);
}


// �u�����h�X�e�[�g���g�p����
void BlendState::Bind(void) {
    //----- �ϐ��錾
	const float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    //----- �u�����h�X�e�[�g�g�p
	GetContext()->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
}
