#ifndef __MESH_BUFFER_H__
#define __MESH_BUFFER_H__

#include <DXGame/DirectX.h>


struct MeshBufferDescription {
    const void* vtx;
    UINT vtxSize;
    UINT vtxCount;
    bool isWrite;
    const void* idx;
    UINT idxSize;
    UINT idxCount;
    D3D11_PRIMITIVE_TOPOLOGY topology;
};


// ���b�V���o�b�t�@�[
class MeshBuffer {
public:
    // �R���X�g���N�^
    // @ Arg1 : �������p�ݒ�
	MeshBuffer(const MeshBufferDescription& desc);
    // �f�X�g���N�^
	~MeshBuffer(void);
    // �R�s�[�R���X�g���N�^
    MeshBuffer(const MeshBuffer& r);


    // ���b�V���o�b�t�@�[�ɏ�������
    // @ Arg1 :
	void Write(void* vtx);
    // �`�悷��
	void Draw(void);


private:
    // ���_�o�b�t�@�[���쐬����
    // @ Ret  : �쐬�ɐ���������
	const HRESULT CreateVertexBuffer(void);
    // �C���f�b�N�X�o�b�t�@�[���쐬����
    // @ Ret  : �쐬�ɐ���������
	const HRESULT CreateIndexBuffer(void);


	ID3D11Buffer* m_vtxBuf;
	ID3D11Buffer* m_idxBuf;
	MeshBufferDescription m_desc;
};

#endif // __MESH_BUFFER_H__