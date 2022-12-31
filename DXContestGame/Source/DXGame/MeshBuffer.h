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


// メッシュバッファー
class MeshBuffer {
public:
    // コンストラクタ
    // @ Arg1 : 初期化用設定
	MeshBuffer(const MeshBufferDescription& desc);
    // デストラクタ
	~MeshBuffer(void);


    // メッシュバッファーに書き込む
    // @ Arg1 :
	void Write(void* vtx);
    // 描画する
	void Draw(void);


private:
    // 頂点バッファーを作成する
    // @ Ret  : 作成に成功したか
	const HRESULT CreateVertexBuffer(void);
    // インデックスバッファーを作成する
    // @ Ret  : 作成に成功したか
	const HRESULT CreateIndexBuffer(void);


	std::unique_ptr<ID3D11Buffer> m_vtxBuf;
	std::unique_ptr<ID3D11Buffer> m_idxBuf;
	MeshBufferDescription m_desc;
};

#endif // __MESH_BUFFER_H__