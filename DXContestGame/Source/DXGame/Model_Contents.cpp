#include "Model.h"
#include "DirectXTex/Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool Model::Load(std::string file, float scale, bool flip)
{
    //assimp�̓ǂݍ��ݎ��̐ݒ�   
    Assimp::Importer impporter;
    int flag = 0;
    flag |= aiProcess_Triangulate;
    flag |= aiProcess_JoinIdenticalVertices;
    flag |= aiProcess_FlipUVs;
    if (!(file.empty())) {
        flag |= aiProcess_MakeLeftHanded;
    }

    //----- assimp�œǂݍ���
    const aiScene* pScene = impporter.ReadFile(file, flag);
    if (!pScene) {
        return false;
    } 

    // �A�j���[�V�����p�̐ݒ�
    m_modelScale = scale;
    m_isModelFlip = flip;
    MakeNodes(pScene);

    //----- �ǂݍ��񂾃f�[�^�����ƂɌ��̃��b�V���̃f�[�^���m��
    m_meshNum = pScene->mNumMeshes;
    m_pMeshes = new Mesh[m_meshNum];

    //----- ���b�V�����Ƃɒ��_�f�[�^���A�C���f�b�N�X�f�[�^��ǂݎ��
    for (unsigned int i = 0; i < m_meshNum; ++i) {
        //----- ���b�V�������ɒ��_�̃f�[�^���m��
        aiVector3D zero(0.0f, 0.0f, 0.0f);
        m_pMeshes[i].vertexNum = pScene->mMeshes[i]->mNumVertices;
        m_pMeshes[i].pVertices = new Model::Vertex[m_pMeshes[i].vertexNum];

        //----- ���b�V�����̒��_�f�[�^�ǂݎ��
        for (unsigned int j = 0; j < m_pMeshes[i].vertexNum; ++j) {
            //----- �l�̋z�o��
            aiVector3D pos = pScene->mMeshes[i]->mVertices[j];
            aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ? pScene->mMeshes[i]->mTextureCoords[0][j] : zero;

            //----- �l��ݒ�
            m_pMeshes[i].pVertices[j] = {
                DirectX::XMFLOAT3(pos.x * scale, pos.y * scale, pos.z * scale),
                DirectX::XMFLOAT3(0,0,0),
                DirectX::XMFLOAT2(uv.x,uv.y),
                {0.0f, 0.0f, 0.0f, 0.0f},
                {0, 0, 0, 0}
            };
        }

        // �A�j���[�V�����p�̐ݒ�
        MakeBoneWeight(pScene, i);

        //----- ���b�V�������ƂɃC���f�b�N�X�̃f�[�^���m��
        //      �� face �̓|���S���̐���\���i1 �|���S���� 3 �C���f�b�N�X�j
        m_pMeshes[i].indexNum = pScene->mMeshes[i]->mNumFaces * 3;
        m_pMeshes[i].pIndices = new unsigned int[m_pMeshes[i].indexNum];

        //----- ���b�V�����̃C���f�b�N�X�f�[�^��ǂݎ��
        for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j) {
            aiFace face = pScene->mMeshes[i]->mFaces[j];
            int idx = j * 3;
            m_pMeshes[i].pIndices[idx + 0] = face.mIndices[0];
            m_pMeshes[i].pIndices[idx + 1] = face.mIndices[1];
            m_pMeshes[i].pIndices[idx + 2] = face.mIndices[2];
        }

        //----- �}�e���A���̊��蓖��
        m_pMeshes[i].materialID = pScene->mMeshes[i]->mMaterialIndex;

        //----- ���b�V�������ɒ��_�o�b�t�@�̍쐬
        MeshBuffer::Description desc = {};
        desc.pVtx = m_pMeshes[i].pVertices;
        desc.vtxSize = sizeof(Vertex);
        desc.vtxCount = m_pMeshes[i].vertexNum;
        desc.pIdx = m_pMeshes[i].pIndices;
        desc.idxSize = sizeof(unsigned int);
        desc.idxCount = m_pMeshes[i].indexNum;
        desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        m_pMeshes[i].pMesh = new MeshBuffer(desc);
    }

    //----- �e�N�X�`����ǂݍ��ޏꏊ������
    std::string dir = file;
    dir = dir.substr(0, dir.find_last_of('/') + 1); // �ǂݍ��ރt�@�C���p�X����t�@�C��������菜��

    //----- �ǂݍ��񂾃f�[�^�����ƂɃ}�e���A���̃f�[�^���m��
    m_materialNum = pScene->mNumMaterials;
    m_pMaterials = new Material[m_materialNum];

    //----- �}�e���A�����ƂɃf�[�^��ǂݎ��
    HRESULT hr;
    for (unsigned int i = 0; i < m_materialNum; ++i) {
        //----- �e�N�X�`���̓ǂݎ��
        aiString path;
        if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS) {
            //----- ���f���t�@�C���ɋL�^����Ă����t�@�C���p�X����ǂݍ���
            hr = LoadTextureFromFile(path.C_Str(), &m_pMaterials[i].pTexture);
            if (FAILED(hr)) {
                //----- ���f���Ɠ����t�@���_���Ńe�N�X�`���t�@�C����ǂݍ���
                std::string file = dir;
                file += path.C_Str();
                hr = LoadTextureFromFile(file.c_str(), &m_pMaterials[i].pTexture);
            }
            //----- �p�X�𕪉����ĒT��
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
    
    return true;
}

void Model::Draw()
{
	m_pVS->Bind();
	m_pPS->Bind();
	for (unsigned int i = 0; i < m_meshNum; ++i)
	{
        UpdateBoneMatrix(i);
		SetTexturePS(m_pMaterials[m_pMeshes[i].materialID].pTexture, 0);
		m_pMeshes[i].pMesh->Draw();
	}
}