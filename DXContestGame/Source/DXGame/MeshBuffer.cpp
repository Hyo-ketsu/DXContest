#include <DXGame/MeshBuffer.h>


// �R���X�g���N�^
MeshBuffer::MeshBuffer(const MeshBufferDescription& desc)
	: m_vtxBuf(nullptr)
	, m_idxBuf(nullptr)
	, m_desc(desc) {
    //----- �o�b�t�@�[�̍쐬
	_ASSERT_EXPR(SUCCEEDED(CreateVertexBuffer()),
		L"Create failed vertex buffer.");
	_ASSERT_EXPR(SUCCEEDED(CreateIndexBuffer()),
		L"Create failed index buffer.");
}
// �f�X�g���N�^
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
// �R�s�[�R���X�g���N�^
MeshBuffer::MeshBuffer(const MeshBuffer& r) {
    m_desc = r.m_desc;
    CreateVertexBuffer();
    CreateIndexBuffer();
}
// ���b�V���o�b�t�@�[�ɏ�������
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
// �`�悷��
void MeshBuffer::Draw(void) {
    //----- �ϐ��錾
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


// ���_�o�b�t�@�[���쐬����
const HRESULT MeshBuffer::CreateVertexBuffer(void)
{
	//--- �쐬����o�b�t�@�̏��
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.vtxSize * m_desc.vtxCount;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (m_desc.isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- �o�b�t�@�̏����l��ݒ�
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.vtx;

	//--- ���_�o�b�t�@�̍쐬
	auto hr = GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_vtxBuf);
    return hr;
}
// �C���f�b�N�X�o�b�t�@�[���쐬����
const HRESULT MeshBuffer::CreateIndexBuffer(void)
{
    if (m_desc.idx == nullptr) return S_FALSE;

	// �o�b�t�@�̏���ݒ�
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = m_desc.idxSize * m_desc.idxCount;
	bufDesc.Usage     = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// �o�b�t�@�̏����f�[�^
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = m_desc.idx;

	// �C���f�b�N�X�o�b�t�@����
    auto hr = GetDevice()->CreateBuffer(&bufDesc, &subResource, &m_idxBuf);
    return hr;
}