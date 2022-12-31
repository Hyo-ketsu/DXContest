#include <DXGame/DirectX.h>


ID3D11Device*           g_device;       // Device
ID3D11DeviceContext*    g_context;      // Context
IDXGISwapChain*         g_swapChain;    // �X���b�v�`�F�C��
ID3D11RenderTargetView* g_RTV;          // �����_�[�^�[�Q�b�g    
ID3D11DepthStencilView* g_DSV;          // �[�x�o�b�t�@


// Device���擾����
ID3D11Device* GetDevice(void) {
	return g_device;
}
// Context���擾����
ID3D11DeviceContext* GetContext(void) {
	return g_context;
}
// SwapChain���擾����
IDXGISwapChain* GetSwapChain(void) {
	return g_swapChain;
}


// DirectX������������
const HRESULT InitDX(HWND hWnd, const UINT width, const UINT height, const bool isFullscreen) {
    //----- �ϐ��錾
	HRESULT	hr = E_FAIL;    // �������ɐ���������

	//----- �X���b�v�`�F�C���̐ݒ�
	// �X���b�v�`�F�C���Ƃ́A�E�C���h�E�ւ̕\���_�u���o�b�t�@���Ǘ�����
	// �}���`�T���v�����O�A���t���b�V�����[�g���ݒ�ł���
	// �����̃o�b�N�o�b�t�@���쐬�ł���
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));                        // �[���N���A
	sd.BufferDesc.Width  = width;                       // �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = height;                      // �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B,A)
	sd.SampleDesc.Count  = 1;                           // �}���`�T���v���̐�
	sd.BufferDesc.RefreshRate.Numerator   = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // �o�b�N�o�b�t�@�̎g�p���@
	sd.BufferCount  = 1;                                // �o�b�N�o�b�t�@�̐�
	sd.OutputWindow = hWnd;                             // �֘A�t����E�C���h�E
	sd.Windowed     = isFullscreen ? FALSE : TRUE;
	sd.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//----- �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
		D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
		D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//----- �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex) {
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�iNULL�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
			driverType,				// �f�o�C�X�h���C�o�̃^�C�v
			NULL,					// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
			createDeviceFlags,		// �f�o�C�X�t���O
			featureLevels,			// �@�\���x��
			numFeatureLevels,		// �@�\���x����
			D3D11_SDK_VERSION,		// 
			&sd,					// �X���b�v�`�F�C���̐ݒ�
			&g_swapChain,			// IDXGIDwapChain�C���^�t�F�[�X	
			&g_device,				// ID3D11Device�C���^�t�F�[�X
			&featureLevel,		// �T�|�[�g����Ă���@�\���x��
			&g_context);		// �f�o�C�X�R���e�L�X�g
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//----- �����_�[�^�[�Q�b�g�쐬
	// �o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D* backBuffer = nullptr;
	hr = g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	// �o�b�N�o�b�t�@�ւ̃|�C���^���w�肵�ă����_�[�^�[�Q�b�g�r���[���쐬
	if (SUCCEEDED(hr)) {
		hr = g_device->CreateRenderTargetView(backBuffer, NULL, &g_RTV);
		g_context->OMSetRenderTargets(1, &g_RTV, nullptr);
	}

    //----- �[�x�o�b�t�@�p�̃e�N�X�`���쐬
    D3D11_TEXTURE2D_DESC dsvTexDesc = {};
    backBuffer->GetDesc(&dsvTexDesc);
    dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    ID3D11Texture2D* pDSVTex;
    hr = g_device->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
    if (FAILED(hr)) { return hr; }

    //----- �[�x�o�b�t�@���쐬
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = dsvTexDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = g_device->CreateDepthStencilView(pDSVTex, &dsvDesc, &g_DSV);
    if (FAILED(hr)) { return hr; }

    //----- �`���i�����_�[�^�[�Q�b�g�j�Ɛ[�x�o�b�t�@��ݒ�
    g_context->OMSetRenderTargets(1, &g_RTV, g_DSV);

	//----- �r���[�|�[�g
	D3D11_VIEWPORT viewPort;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width    = width;
	viewPort.Height   = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	g_context->RSSetViewports(1, &viewPort);

	return S_OK;
}


// DirectX���I������
void UninitDX(void) {
	g_context->ClearState();
	g_context->Release();
	g_swapChain->SetFullscreenState(false, NULL);
	g_swapChain->Release();
	g_device->Release();
}


// �`��O����
void BeginDrawDX(void) {
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	g_context->ClearRenderTargetView(g_RTV, color);
    g_context->ClearDepthStencilView(g_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
// �`��㏈��
void EndDrawDX(void) {
	g_swapChain->Present(0, 0);
}


// �[�x�o�b�t�@��L���ɂ��邩
void EnableDepth(const bool isEnable) {
    if (isEnable) {
        //----- �`���i�����_�[�^�[�Q�b�g�j�Ɛ[�x�o�b�t�@��ݒ�
        g_context->OMSetRenderTargets(1, &g_RTV, g_DSV);
    }
    else {
        //----- �`���i�����_�[�^�[�Q�b�g�j�Ɛ[�x�o�b�t�@��ݒ�
        g_context->OMSetRenderTargets(1, &g_RTV, nullptr);
    }
}
