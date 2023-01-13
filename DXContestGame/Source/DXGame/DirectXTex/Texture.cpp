#include <DXGame/DirectXTex/Texture.h>

// �v���b�g�t�H�[��
#if _WIN64
#define PLATFORM "x64"
#elif _WIN32
#define PLATFORM "x86"
#endif
// �\��
#define CONFIG "Debug"
// ���C�u�������
#define DXTEX_LIB_PATH "DirectXTex/" PLATFORM "/" CONFIG "/DirectXTex.lib"

//----- ���C�u���������N
#pragma comment(lib, DXTEX_LIB_PATH)


ID3D11Device* g_pTextureDevice;

HRESULT InitTexture(ID3D11Device* pDevice) {
	g_pTextureDevice = pDevice;
	return S_OK;
}
void UninitTexture() {
	g_pTextureDevice = nullptr;
}

HRESULT LoadTextureFromFile(const char* fileName, ID3D11ShaderResourceView** ppTex) {
	HRESULT hr = E_FAIL;
	
	//--- �����ϊ�
	wchar_t wFilePath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fileName, -1, wFilePath, sizeof(wFilePath));

	// windows�Ή��t�H�[�}�b�g�̉摜�ǂݍ���
	DirectX::TexMetadata info;
	DirectX::ScratchImage image;
	hr = DirectX::LoadFromWICFile(wFilePath, DirectX::WIC_FLAGS_NONE, &info, image);
	if (FAILED(hr))
	{
		hr = DirectX::LoadFromTGAFile(wFilePath, &info, image);
	}
	if (SUCCEEDED(hr))
	{
		hr = DirectX::CreateShaderResourceView(
			g_pTextureDevice, image.GetImages(), image.GetImageCount(), info, ppTex);
	}

	return hr;
}

HRESULT CreateRenderTarget(float width, float height, ID3D11ShaderResourceView** ppTex, ID3D11RenderTargetView** ppRenderTarget) {
	return S_OK;
}