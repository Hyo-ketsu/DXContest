#include <DXGame/BlendState.h>


// コンストラクタ
BlendState::BlendState(void)
	: m_blendState(nullptr) {
}
// デストラクタ
BlendState::~BlendState(void) {
    //----- 終了処理
	if (m_blendState != nullptr) {
		m_blendState->Release();
	}
}


// ブレンドステートの作成
HRESULT BlendState::Create(const D3D11_RENDER_TARGET_BLEND_DESC desc) {
    //----- 変数宣言
	D3D11_BLEND_DESC  blendDesc;            // 初期化情報
    HRESULT           ret;                  // 生成に成功したかを返却する

    //----- 初期化と代入
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0] = desc;

    //----- ブレンドステート作成
    return GetDevice()->CreateBlendState(&blendDesc, &m_blendState);
}


// ブレンドステートを使用する
void BlendState::Bind(void) {
    //----- 変数宣言
	const float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    //----- ブレンドステート使用
	GetContext()->OMSetBlendState(m_blendState, blendFactor, 0xffffffff);
}
