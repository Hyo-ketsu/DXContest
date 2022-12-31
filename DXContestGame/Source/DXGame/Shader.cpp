#include <DXGame/Shader.h>


//----------
// 基本クラス
Shader::Shader(Kind kind)
	: m_kind(kind) {
}
Shader::~Shader(void) {
}
HRESULT Shader::Load(const char* fileName) {
	HRESULT hr = E_FAIL;

	// ファイルを読み込む
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);
	fclose(fp);

	// シェーダー作成
	hr = MakeShader(pData, fileSize);

	// 終了処理
	if (pData) { delete[] pData; }
	return hr;
}
HRESULT Shader::Compile(const char* code) {
	static const char* pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0"
	};

	HRESULT hr;
	ID3DBlob* pBlob;
	ID3DBlob* error;
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	hr = D3DCompile(code, strlen(code), nullptr, nullptr, nullptr,
		"main", pTargetList[m_kind], compileFlag, 0, &pBlob, &error);
	if (FAILED(hr)) { return hr; }

	// シェーダ作成
	hr = MakeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize());
	if (pBlob) pBlob->Release();
	if (error) error->Release();
	return hr;
}



//----------
// 頂点シェーダ
VertexShader::ILList VertexShader::m_ilList;
void VertexShader::ReleaseInputLayout() {
	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end()) {
		it->second->Release();
		++it;
	}
}

VertexShader::VertexShader()
	: Shader(Shader::VertexShader)
	, m_VS(nullptr)
	, m_inputLayout(nullptr) {
}
VertexShader::~VertexShader() {
	if (m_VS) {
		m_VS->Release();
		m_VS = nullptr;
	}
}
void VertexShader::Bind(void) {
	ID3D11DeviceContext* pContext = GetContext();
	pContext->VSSetShader(m_VS, NULL, 0);
	pContext->IASetInputLayout(m_inputLayout);
}
HRESULT VertexShader::MakeShader(void* data, UINT size) {
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(data, size, NULL, &m_VS);
	if (FAILED(hr)) { return hr; }

	/*
	シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
	セマンティクスの配置などから識別子を作成
	識別子が登録済→再利用、なければ新規作成
	https://blog.techlab-xe.net/dxc-shader-reflection/
	*/

	ID3D11ShaderReflection* reflection;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* inputDesc;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;
	std::string key = "";

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		}, {
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		}, {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	hr = D3DReflect(data, size, IID_PPV_ARGS(&reflection));
	if (FAILED(hr)) { return hr; }

	reflection->GetDesc(&shaderDesc);
	inputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	for (int i = 0; i < shaderDesc.InputParameters; ++i) {
		reflection->GetInputParameterDesc(i, &sigDesc);
		inputDesc[i].SemanticName = sigDesc.SemanticName;
		inputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		// http://marupeke296.com/TIPS_No17_Bit.html
		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

		switch (sigDesc.ComponentType) {
		case D3D_REGISTER_COMPONENT_UINT32:
			inputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			inputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			inputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		inputDesc[i].InputSlot = 0;
		inputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		inputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[i].InstanceDataStepRate = 0;

		key += sigDesc.SemanticName;
		key += '0' + sigDesc.SemanticIndex;
	}

	ILList::iterator it = m_ilList.begin();
	while (it != m_ilList.end()) {
		if (it->first == key)
		{
			m_inputLayout = it->second;
			break;
		}
		++it;
	}
	if (it == m_ilList.end()) {
		hr = pDevice->CreateInputLayout(
			inputDesc, shaderDesc.InputParameters,
			data, size, &m_inputLayout
		);
		if (SUCCEEDED(hr)) {
			m_ilList.insert(ILKey(key, m_inputLayout));
		}
	}

	delete[] inputDesc;
	return hr;
}
//----------
// ピクセルシェーダ
PixelShader::PixelShader()
	: Shader(Shader::PixelShader)
	, m_PS(nullptr) {
}
PixelShader::~PixelShader() {
	if (m_PS)
	{
		m_PS->Release();
		m_PS = nullptr;
	}
}
void PixelShader::Bind(void) {
    GetContext()->PSSetShader(m_PS, nullptr, 0);
}
HRESULT PixelShader::MakeShader(void* data, UINT size) {
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	hr = pDevice->CreatePixelShader(data, size, NULL, &m_PS);
	return hr;
}

void SetTextureVS(ID3D11ShaderResourceView* tex, UINT slot) {
	GetContext()->VSSetShaderResources(slot, 1, &tex);
}
void SetTexturePS(ID3D11ShaderResourceView* tex, UINT slot) {
	GetContext()->PSSetShaderResources(slot, 1, &tex);
}