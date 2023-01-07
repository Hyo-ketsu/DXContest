#include <DXGame/MeshBuffer.h>


// コンストラクタ
MeshBuffer::MeshBuffer(const MeshBufferDescription& desc)
	: m_vtxBuf(nullptr)
	, m_idxBuf(nullptr)
	, m_desc(desc) {
    //----- バッファーの作成
	_ASSERT_EXPR(SUCCEEDED(CreateVertexBuffer()),
		L"Create failed vertex buffer.");
	_ASSERT_EXPR(SUCCEEDED(CreateIndexBuffer()),
		L"Create failed index buffer.");
}
// デストラクタ
MeshBuffer::~MeshBuffer(void) {
	if (m_vtxBuf != nullptr) {
		m_vtxBuf->Release();
        m_vtxBuf = nullptr;
	}
	if (m_idxBuf != nullptr) {
		m_idxBuf->Release();
        m_idxBuf = nullptr;
	}
}
// コピーコンストラクタ
MeshBuffer::MeshBuffer(const MeshBuffer& r) {
    m_desc = r.m_desc;
    CreateVertexBuffer();
    CreateIndexBuffer();
}
// メッシュバッファーに書き込む
void MeshBuffer::Write(void* pVtx) {
	if (!m_desc.isWrite) { return; }

	D3D11_MAPPED_SUBRESOURCE mapResource;

	if (FAILED(GetContext()->Map(m_vtxBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource))) {
		return;
	}

	rsize_t size = m_desc.vtxCount * m_desc.vtxSize;
	memcpy_s(mapResource.pData, size, pVtx, size);
    GetContext()->Unmap(m_vtxBuf, 0);
}
// 描画する
void MeshBuffer::Draw(void) {
    //----- 変数宣言
	UINT offset = 0;

    GetContext()->IASetPrimitiveTopology(m_desc.topology);
    GetContext()->IASetVertexBuffers(0, 1, &m_vtxBuf, &m_desc.vtxSize, &offset);

	if (m_idxBuf) {
		DXGI_FORMAT format;
		switch (m_desc.idxSize)
		{
		default: _ASSERT_EXPR(false, "undefined index size."); break;
		case 1: format = DXGI_FORMAT_R8_UINT;  break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		}
        GetContext()->IASetIndexBuffer(m_idxBuf, format, 0);
        GetContext()->DrawIndexed(m_desc.idxCount, 0, 0);
	}
	else {
        GetContext()->Draw(m_desc.vtxCount, 0);
	}
}


// 頂点バッファーを作成する
const HRESULT MeshBuffer::CreateVertexBuffer(void)
{
	//--- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.vtxSize * m_desc.vtxCount;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (m_desc.isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.vtx;

	//--- 頂点バッファの作成
	auto hr = GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_vtxBuf);
    return hr;
}
// インデックスバッファーを作成する
const HRESULT MeshBuffer::CreateIndexBuffer(void)
{
    if (m_desc.idx == nullptr) return S_FALSE;

	// バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.idxSize * m_desc.idxCount;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.idx;

	// インデックスバッファ生成
    auto hr = GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_idxBuf);
    return hr;
}