#ifndef __CONSTANT_BUFFER_H__
#define __CONSTANT_BUFFER_H__

#include <DXGame/DirectX.h>


// �萔�o�b�t�@
class ConstantBuffer {
public:
    // �R���X�g���N�^
	ConstantBuffer(void);
    // �f�X�g���N�^
	~ConstantBuffer(void);


    // �萔�o�b�t�@���쐬����
    // @ Ret  : ����������
    // @ Arg1 : �쐬�T�C�Y
	HRESULT Create(const UINT size);


    // �萔�o�b�t�@�̏�������
    // @ Arg1 : 
	void Write(const void* pData);


    // ���_�V�F�[�_�[�̐ݒ�
    // @ Arg1 : �ǂ̈ʒu�Ɋi�[���邩
	void BindVS(const UINT slot);
    // �s�N�Z���V�F�[�_�[�̐ݒ�
    // @ Arg1 : �ǂ̈ʒu�Ɋi�[���邩
	void BindPS(const UINT slot);

private:
	ID3D11Buffer* m_constantBuffer; // �萔�o�b�t�@���i�[���Ă���
};

#endif // __CONSTANT_BUFFER_H__