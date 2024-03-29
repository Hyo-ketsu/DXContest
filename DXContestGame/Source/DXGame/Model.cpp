#include <DXGame/Model.h>
#include <DXGame/DirectXTex/Texture.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


VertexShader* Model::m_pDefVS = nullptr;
PixelShader* Model::m_pDefPS  = nullptr;
unsigned int Model::m_shaderRef = 0;

//--- プロトタイプ宣言
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

Model::Model()
{
    if (m_shaderRef == 0)
    {
        MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
    }
    m_pVS = m_pDefVS;
    m_pPS = m_pDefPS;
    ++m_shaderRef;
}
Model::~Model()
{
    for (unsigned int i = 0; i < m_meshNum; ++i)
    {
        delete[] m_pMeshes[i].pVertices;
        delete[] m_pMeshes[i].pIndices;
        delete m_pMeshes[i].pMesh;
    }
    delete[] m_pMeshes;

    --m_shaderRef;
    if (m_shaderRef <= 0)
    {
        delete m_pDefPS;
        delete m_pDefVS;
    }
}

void Model::SetVertexShader(VertexShader* vs)
{
    m_pVS = vs;
}
void Model::SetPixelShader(PixelShader* ps)
{
    m_pPS = ps;
}
const Model::Mesh* Model::GetMesh(unsigned int index)
{
    if (index >= GetMeshNum())
    {
        return &m_pMeshes[index];
    }
    return nullptr;
}
uint32_t Model::GetMeshNum()
{
    return m_meshNum;
}
const std::string Model::LoadFileName(void) const {
    return m_fileName;
}

void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
    const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.uv = vin.uv;
	return vout;
})EOT";
    const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
    *vs = new VertexShader();
    (*vs)->Compile(ModelVS);
    *ps = new PixelShader();
    (*ps)->Compile(ModelPS);
}


bool Model::Load(std::string file, float scale, bool flip)
{
    //assimpの読み込み時の設定   
    Assimp::Importer impporter;
    int flag = 0;
    flag |= aiProcess_Triangulate;
    //flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_JoinIdenticalVertices;
    flag |= aiProcess_FlipUVs;
    if (flip) flag |= aiProcess_MakeLeftHanded;

    //----- assimpで読み込み
    const aiScene* pScene = impporter.ReadFile(file, flag);
    if (!pScene) {
        return false;
    }

    //----- 読み込んだデータをもとに元のメッシュのデータを確保
    m_meshNum = pScene->mNumMeshes;
    m_pMeshes = new Mesh[m_meshNum];

    //----- メッシュごとに頂点データを、インデックスデータを読み取り
    for (unsigned int i = 0; i < m_meshNum; ++i) {
        //----- メッシュを元に頂点のデータを確保
        aiVector3D zero(0.0f, 0.0f, 0.0f);
        m_pMeshes[i].vertexNum = pScene->mMeshes[i]->mNumVertices;
        m_pMeshes[i].pVertices = new Model::Vertex[m_pMeshes[i].vertexNum];

        //----- メッシュ内の頂点データ読み取り
        for (unsigned int j = 0; j < m_pMeshes[i].vertexNum; ++j) {
            //----- 値の吸出し
            aiVector3D pos = pScene->mMeshes[i]->mVertices[j];
            aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ? pScene->mMeshes[i]->mTextureCoords[0][j] : zero;

            //----- 値を設定
            m_pMeshes[i].pVertices[j] = {
                DirectX::XMFLOAT3(pos.x * scale, pos.y * scale, pos.z * scale),
                DirectX::XMFLOAT2(uv.x,uv.y),
            };
        }

        //----- メッシュをもとにインデックスのデータを確保
        //      ※ face はポリゴンの数を表す（1 ポリゴンで 3 インデックス）
        m_pMeshes[i].indexNum = pScene->mMeshes[i]->mNumFaces * 3;
        m_pMeshes[i].pIndices = new unsigned int[m_pMeshes[i].indexNum];

        //----- メッシュ内のインデックスデータを読み取り
        for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j) {
            aiFace face = pScene->mMeshes[i]->mFaces[j];
            int idx = j * 3;
            m_pMeshes[i].pIndices[idx + 0] = face.mIndices[0];
            m_pMeshes[i].pIndices[idx + 1] = face.mIndices[1];
            m_pMeshes[i].pIndices[idx + 2] = face.mIndices[2];
        }

        //----- マテリアルの割り当て
        m_pMeshes[i].materialID = pScene->mMeshes[i]->mMaterialIndex;

        //----- メッシュを元に頂点バッファの作成
        MeshBufferDescription desc = {};
        desc.vtx = m_pMeshes[i].pVertices;
        desc.vtxSize = sizeof(Vertex);
        desc.vtxCount = m_pMeshes[i].vertexNum;
        desc.idx = m_pMeshes[i].pIndices;
        desc.idxSize = sizeof(unsigned int);
        desc.idxCount = m_pMeshes[i].indexNum;
        desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        m_pMeshes[i].pMesh = new MeshBuffer(desc);
    }

    //----- テクスチャを読み込む場所を検索
    std::string dir = file;
    dir = dir.substr(0, dir.find_last_of('/') + 1); // 読み込むファイルパスからファイル名を取り除く

    //----- 読み込んだデータをもとにマテリアルのデータを確保
    m_materialNum = pScene->mNumMaterials;
    m_pMaterials = new Material[m_materialNum];

    //----- マテリアルごとにデータを読み取り
    HRESULT hr;
    for (unsigned int i = 0; i < m_materialNum; ++i) {
        //----- テクスチャの読み取り
        aiString path;
        if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS) {
            //----- モデルファイルに記録されていたファイルパスから読み込み
            hr = LoadTextureFromFile(path.C_Str(), &m_pMaterials[i].pTexture);
            if (FAILED(hr)) {
                //----- モデルと同じファルダ内でテクスチャファイルを読み込み
                std::string file = dir;
                file += path.C_Str();
                hr = LoadTextureFromFile(file.c_str(), &m_pMaterials[i].pTexture);
            }
            //----- パスを分解して探索
            if (FAILED(hr)) {
                std::string flie = path.C_Str();
                for (auto fileIt = file.begin(); fileIt != file.end(); fileIt++) {
                    if (*fileIt == '/') {
                        *fileIt = '\\';
                    }
                    file = file.substr(file.find_last_of('\\') + 1);
                    file = dir + file;
                    hr = LoadTextureFromFile(file.c_str(), &m_pMaterials[i].pTexture);
                }
            }
            if (FAILED(hr)) { return false; }
        }
        else {
            m_pMaterials[i].pTexture = nullptr;
        }
    }

    m_fileName = file;
    return true;
}

void Model::Draw()
{
    m_pVS->Bind();
    m_pPS->Bind();
    for (unsigned int i = 0; i < m_meshNum; ++i)
    {
        SetTexturePS(m_pMaterials[m_pMeshes[i].materialID].pTexture, 0);
        m_pMeshes[i].pMesh->Draw();
    }
}