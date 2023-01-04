#include <DXGame/ConstantBuffer.h>


// �R���X�g���N�^
ConstantBuffer::ConstantBuffer(void)
	: m_constantBuffer(nullptr) {
}
// �f�X�g���N�^
ConstantBuffer::~ConstantBuffer(void) {
    //----- �I������
	if (m_constantBuffer != nullptr) {
		m_constantBuffer->Release();
        m_constantBuffer = nullptr;
	}
}


// �萔�o�b�t�@���쐬����
HRESULT ConstantBuffer::Create(const UINT size) {
    //----- �ϐ��錾
	HRESULT ret;    // �����������̕ԋp�p

	//----- �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//----- �o�b�t�@�̍쐬
	ret = GetDevice()->CreateBuffer(&bufDesc, nullptr, &m_constantBuffer);

    //----- �ԋp
	return ret;
}


// �萔�o�b�t�@�̏�������
void ConstantBuffer::Write(const void* pData) {
	//----- �萔�o�b�t�@�ւ̏�������
    GetContext()->UpdateSubresource(m_constantBuffer, 0, nullptr, pData, 0, 0);
}


// ���_�V�F�[�_�[�̐ݒ�
void ConstantBuffer::BindVS(UINT slot) {
	// �萔�o�b�t�@�̃f�[�^�𑗂�ہA
	// �ǂ̈ʒu�Ɋi�[���邩��1�ڂ̈���(StartSlot)��
	// �w�肷��B
	// hlsl�̃R�[�h�ł�register(bX)�Ńo�b�t�@�̊i�[
	// �ʒu�����߂Ă����B
    GetContext()->VSSetConstantBuffers(slot, 1, &m_constantBuffer);
}
// �s�N�Z���V�F�[�_�[�̐ݒ�
void ConstantBuffer::BindPS(UINT slot) {
    GetContext()->PSSetConstantBuffers(slot, 1, &m_constantBuffer);
}
