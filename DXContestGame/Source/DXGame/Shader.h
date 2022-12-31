#ifndef __SHADER_H__
#define __SHADER_H__

#include <DXGame/DirectX.h>


// �V�F�[�_�[�̊�{�N���X
class Shader {
protected:
	enum Kind {
		VertexShader,
		PixelShader
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader(void);
public:
	// �V�F�[�_�[�t�@�C��(*.cso)��ǂݍ��ޏ���
	HRESULT Load(const char* fileName);
	// �����񂩂�V�F�[�_���R���p�C��
	HRESULT Compile(const char* code);


	// �V�F�[�_�[��`��Ɏg�p
	virtual void Bind(void) = 0;

protected:
	// �V�F�[�_�[�t�@�C����ǂݍ��񂾌�A�V�F�[�_�[�̎�ޕʂɏ������s��
	virtual HRESULT MakeShader(void* data, UINT size) = 0;

private:
	Kind m_kind;
};

//----------
// ���_�V�F�[�_
class VertexShader : public Shader {
private:
	using ILKey = std::pair<std::string, ID3D11InputLayout*>;
	using ILList = std::unordered_map<std::string, ID3D11InputLayout*>;
public:
	static void ReleaseInputLayout();

	VertexShader(void);
	~VertexShader(void);
	void Bind(void);
protected:
	HRESULT MakeShader(void* data, UINT size);

private:
	static ILList m_ilList;
	ID3D11VertexShader* m_VS;
	ID3D11InputLayout* m_inputLayout;
};
//----------
// �s�N�Z���V�F�[�_
class PixelShader : public Shader {
public:
	PixelShader(void);
	~PixelShader(void);
	void Bind(void);
protected:
	HRESULT MakeShader(void* data, UINT size);
private:
	ID3D11PixelShader* m_PS;
};


//--- �e�N�X�`��
void SetTextureVS(ID3D11ShaderResourceView* tex, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* tex, UINT slot = 0);

#endif