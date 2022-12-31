#include <DXGame/ConstantBuffer.h>


// コンストラクタ
ConstantBuffer::ConstantBuffer(void)
	: m_constantBuffer(nullptr) {
}
// デストラクタ
ConstantBuffer::~ConstantBuffer(void) {
    //----- 終了処理
	if (m_constantBuffer != nullptr) {
		m_constantBuffer->Release();
	}
}


// 定数バッファを作成する
HRESULT ConstantBuffer::Create(const UINT size) {
    //----- 変数宣言
    ID3D11Buffer* constantBuffer = nullptr; // 初期化用生ポインタ
	HRESULT       ret;                      // 成功したかの返却用

	//----- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//----- バッファの作成
	ret = GetDevice()->CreateBuffer(&bufDesc, nullptr, &constantBuffer);
    m_constantBuffer = std::unique_ptr<std::remove_reference<decltype(*constantBuffer)>::type>(constantBuffer);

    //----- 返却
	return ret;
}


// 定数バッファの書き込み
void ConstantBuffer::Write(const void* pData) {
	//----- 定数バッファへの書き込み
    GetContext()->UpdateSubresource(m_constantBuffer.get(), 0, nullptr, pData, 0, 0);
}


// 頂点シェーダーの設定
void ConstantBuffer::BindVS(UINT slot) {
	// 定数バッファのデータを送る際、
	// どの位置に格納するかを1つ目の引数(StartSlot)に
	// 指定する。
	// hlslのコードではregister(bX)でバッファの格納
	// 位置を決めておく。
    auto constantBuffer = m_constantBuffer.get();
    GetContext()->VSSetConstantBuffers(slot, 1, &constantBuffer);
}
// ピクセルシェーダーの設定
void ConstantBuffer::BindPS(UINT slot) {
    auto constantBuffer = m_constantBuffer.get();
    GetContext()->PSSetConstantBuffers(slot, 1, &constantBuffer);
}
