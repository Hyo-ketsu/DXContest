#ifndef __SHADER_H__
#define __SHADER_H__

#include <DXGame/DirectX.h>


// シェーダーの基本クラス
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
	// シェーダーファイル(*.cso)を読み込む処理
	HRESULT Load(const char* fileName);
	// 文字列からシェーダをコンパイル
	HRESULT Compile(const char* code);


	// シェーダーを描画に使用
	virtual void Bind(void) = 0;

protected:
	// シェーダーファイルを読み込んだ後、シェーダーの種類別に処理を行う
	virtual HRESULT MakeShader(void* data, UINT size) = 0;

private:
	Kind m_kind;
};

//----------
// 頂点シェーダ
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
// ピクセルシェーダ
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


//--- テクスチャ
void SetTextureVS(ID3D11ShaderResourceView* tex, UINT slot = 0);
void SetTexturePS(ID3D11ShaderResourceView* tex, UINT slot = 0);

#endif