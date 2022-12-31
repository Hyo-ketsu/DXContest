#include <DXGame/DirectX.h>


ID3D11Device*           g_device;       // Device
ID3D11DeviceContext*    g_context;      // Context
IDXGISwapChain*         g_swapChain;    // スワップチェイン
ID3D11RenderTargetView* g_RTV;          // レンダーターゲット    
ID3D11DepthStencilView* g_DSV;          // 深度バッファ


// Deviceを取得する
ID3D11Device* GetDevice(void) {
	return g_device;
}
// Contextを取得する
ID3D11DeviceContext* GetContext(void) {
	return g_context;
}
// SwapChainを取得する
IDXGISwapChain* GetSwapChain(void) {
	return g_swapChain;
}


// DirectXを初期化する
const HRESULT InitDX(HWND hWnd, const UINT width, const UINT height, const bool isFullscreen) {
    //----- 変数宣言
	HRESULT	hr = E_FAIL;    // 初期化に成功したか

	//----- スワップチェインの設定
	// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
	// マルチサンプリング、リフレッシュレートが設定できる
	// 複数のバックバッファが作成できる
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));                        // ゼロクリア
	sd.BufferDesc.Width  = width;                       // バックバッファの幅
	sd.BufferDesc.Height = height;                      // バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // バックバッファフォーマット(R,G,B,A)
	sd.SampleDesc.Count  = 1;                           // マルチサンプルの数
	sd.BufferDesc.RefreshRate.Numerator   = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // バックバッファの使用方法
	sd.BufferCount  = 1;                                // バックバッファの数
	sd.OutputWindow = hWnd;                             // 関連付けるウインドウ
	sd.Windowed     = isFullscreen ? FALSE : TRUE;
	sd.Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//----- ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	//----- 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex) {
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&sd,					// スワップチェインの設定
			&g_swapChain,			// IDXGIDwapChainインタフェース	
			&g_device,				// ID3D11Deviceインタフェース
			&featureLevel,		// サポートされている機能レベル
			&g_context);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	if (FAILED(hr)) {
		return hr;
	}

	//----- レンダーターゲット作成
	// バックバッファのポインタを取得
	ID3D11Texture2D* backBuffer = nullptr;
	hr = g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
	// バックバッファへのポインタを指定してレンダーターゲットビューを作成
	if (SUCCEEDED(hr)) {
		hr = g_device->CreateRenderTargetView(backBuffer, NULL, &g_RTV);
		g_context->OMSetRenderTargets(1, &g_RTV, nullptr);
	}

    //----- 深度バッファ用のテクスチャ作成
    D3D11_TEXTURE2D_DESC dsvTexDesc = {};
    backBuffer->GetDesc(&dsvTexDesc);
    dsvTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    dsvTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    ID3D11Texture2D* pDSVTex;
    hr = g_device->CreateTexture2D(&dsvTexDesc, nullptr, &pDSVTex);
    if (FAILED(hr)) { return hr; }

    //----- 深度バッファを作成
    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
    dsvDesc.Format = dsvTexDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = g_device->CreateDepthStencilView(pDSVTex, &dsvDesc, &g_DSV);
    if (FAILED(hr)) { return hr; }

    //----- 描画先（レンダーターゲット）と深度バッファを設定
    g_context->OMSetRenderTargets(1, &g_RTV, g_DSV);

	//----- ビューポート
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


// DirectXを終了する
void UninitDX(void) {
	g_context->ClearState();
	g_context->Release();
	g_swapChain->SetFullscreenState(false, NULL);
	g_swapChain->Release();
	g_device->Release();
}


// 描画前処理
void BeginDrawDX(void) {
	float color[4] = { 0.8f, 0.8f, 0.9f, 1.0f };
	g_context->ClearRenderTargetView(g_RTV, color);
    g_context->ClearDepthStencilView(g_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
// 描画後処理
void EndDrawDX(void) {
	g_swapChain->Present(0, 0);
}


// 深度バッファを有効にするか
void EnableDepth(const bool isEnable) {
    if (isEnable) {
        //----- 描画先（レンダーターゲット）と深度バッファを設定
        g_context->OMSetRenderTargets(1, &g_RTV, g_DSV);
    }
    else {
        //----- 描画先（レンダーターゲット）と深度バッファを設定
        g_context->OMSetRenderTargets(1, &g_RTV, nullptr);
    }
}
