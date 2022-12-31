#include <DXGame/Sprite.h>


std::unique_ptr<MeshBuffer>     Sprite::m_mesh;
std::unique_ptr<ConstantBuffer> Sprite::m_buf[2];
DirectX::XMFLOAT4X4             Sprite::m_matrix[3];
DirectX::XMFLOAT4               Sprite::m_param[3];
ID3D11ShaderResourceView*       Sprite::m_texture;
VertexShader*                   Sprite::m_VS;
PixelShader*                    Sprite::m_PS;
std::unique_ptr<VertexShader>   Sprite::m_defVS;
std::unique_ptr<PixelShader>    Sprite::m_defPS;


void Sprite::Init(void) {
	const char* VS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float2 offset;
	float2 size;
	float2 uvPos;
	float2 uvScale;
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.xy *= size;
	vout.pos.xy += offset;
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	vout.uv *= uvScale;
	vout.uv += uvPos;
	vout.color = color;
	return vout;
})EOT";
	const char* PS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET {
	return tex.Sample(samp, pin.uv) * pin.color;
})EOT";

	struct Vertex {
		float pos[3];
		float uv[2];
	} vtx[] = {
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {1.0f, 1.0f}},
	};

	// メッシュ
	MeshBufferDescription desc = {};
	desc.vtx      = vtx;
	desc.vtxSize  = sizeof(Vertex);
	desc.vtxCount = _countof(vtx);
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_mesh = std::unique_ptr<std::remove_reference<decltype(*m_mesh.get())>::type>(new MeshBuffer(desc));

	// 定数バッファ
    m_buf[0] = std::make_unique<std::remove_reference<decltype(*m_buf[0].get())>::type>();
	m_buf[0]->Create(sizeof(m_matrix));
    m_buf[1] = std::make_unique<std::remove_reference<decltype(*m_buf[1].get())>::type>();
	m_buf[1]->Create(sizeof(m_param));

	// パラメーター
	m_param[0] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_param[1] = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_param[2] = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMStoreFloat4x4(&m_matrix[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_matrix[1], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_matrix[2], DirectX::XMMatrixIdentity());

	// シェーダー
	m_defVS = std::make_unique<std::remove_reference<decltype(*m_defVS.get())>::type>();
	m_defVS->Compile(VS);
	m_defPS = std::make_unique<std::remove_reference<decltype(*m_defPS.get())>::type>();
	m_defPS->Compile(PS);
	m_VS = m_defVS.get();
	m_PS = m_defPS.get();
}
void Sprite::Uninit(void) {
}
void Sprite::Draw() {
	m_VS->Bind();
	m_PS->Bind();
	m_buf[0]->Write(m_matrix);
	m_buf[0]->BindVS(0);
	m_buf[1]->Write(m_param);
	m_buf[1]->BindVS(1);
	SetTexturePS(m_texture);
	m_mesh->Draw();
}

void Sprite::SetOffset(DirectX::XMFLOAT2 offset) {
	m_param[0].x = offset.x;
	m_param[0].y = offset.y;
}
void Sprite::SetSize(DirectX::XMFLOAT2 size) {
	m_param[0].z = size.x;
	m_param[0].w = size.y;
}

void Sprite::SetUVPos(DirectX::XMFLOAT2 pos) {
	m_param[1].x = pos.x;
	m_param[1].y = pos.y;
}
void Sprite::SetUVScale(DirectX::XMFLOAT2 scale) {
	m_param[1].x = scale.x;
	m_param[1].y = scale.y;
}
void Sprite::SetColor(DirectX::XMFLOAT4 color) {
	m_param[2] = color;
}
void Sprite::SetTexture(ID3D11ShaderResourceView* tex) {
	m_texture = tex;
}
void Sprite::SetWorld(DirectX::XMFLOAT4X4 world) {
	m_matrix[0] = world;
}
void Sprite::SetView(DirectX::XMFLOAT4X4 view) {
	m_matrix[1] = view;
}
void Sprite::SetProjection(DirectX::XMFLOAT4X4 proj) {
	m_matrix[2] = proj;
}
void Sprite::SetDefaultVertexShader(void) {
	m_VS = m_defVS.get();
}
void Sprite::SetDefaultPixelShader() {
	m_PS = m_defPS.get();
}
void Sprite::SetVertexShader(VertexShader* VS) {
	m_VS = VS;
}
void Sprite::SetPixelShader(PixelShader* PS) {
	m_PS = PS;
}
