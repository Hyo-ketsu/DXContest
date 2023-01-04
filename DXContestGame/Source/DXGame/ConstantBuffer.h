#ifndef __CONSTANT_BUFFER_H__
#define __CONSTANT_BUFFER_H__

#include <DXGame/DirectX.h>


// 定数バッファ
class ConstantBuffer {
public:
    // コンストラクタ
	ConstantBuffer(void);
    // デストラクタ
	~ConstantBuffer(void);


    // 定数バッファを作成する
    // @ Ret  : 成功したか
    // @ Arg1 : 作成サイズ
	HRESULT Create(const UINT size);


    // 定数バッファの書き込み
    // @ Arg1 : 
	void Write(const void* pData);


    // 頂点シェーダーの設定
    // @ Arg1 : どの位置に格納するか
	void BindVS(const UINT slot);
    // ピクセルシェーダーの設定
    // @ Arg1 : どの位置に格納するか
	void BindPS(const UINT slot);

private:
	ID3D11Buffer* m_constantBuffer; // 定数バッファを格納しておく
};

#endif // __CONSTANT_BUFFER_H__