#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <DXGame/MeshBuffer.h>
#include <DXGame/ConstantBuffer.h>
#include <DXGame/Shader.h>


class Sprite {
public:
	static void Init(void);
	static void Uninit(void);
	static void Draw(void);

	static void SetOffset(DirectX::XMFLOAT2 offset);
	static void SetSize(DirectX::XMFLOAT2 size);
	static void SetUVPos(DirectX::XMFLOAT2 pos);
	static void SetUVScale(DirectX::XMFLOAT2 scale);
	static void SetColor(DirectX::XMFLOAT4 color);
	static void SetTexture(ID3D11ShaderResourceView* tex);

	static void SetWorld(DirectX::XMFLOAT4X4 world);
	static void SetView(DirectX::XMFLOAT4X4 view);
	static void SetProjection(DirectX::XMFLOAT4X4 proj);

	static void SetDefaultVertexShader(void);
	static void SetDefaultPixelShader(void);
	static void SetVertexShader(VertexShader* VS);
	static void SetPixelShader(PixelShader* PS);

private:
	static std::unique_ptr<MeshBuffer>     m_mesh;
	static std::unique_ptr<ConstantBuffer> m_buf[2];
	static DirectX::XMFLOAT4X4             m_matrix[3];
	static DirectX::XMFLOAT4               m_param[3];
	static ID3D11ShaderResourceView*       m_texture;
	static VertexShader*                   m_VS;
	static PixelShader*                    m_PS;
	static std::unique_ptr<VertexShader>   m_defVS;
	static std::unique_ptr<PixelShader>    m_defPS;
};


#endif // __SPRITE_H__