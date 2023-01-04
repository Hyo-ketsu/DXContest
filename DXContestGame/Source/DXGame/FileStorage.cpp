#include <DXGame/FileStorage.h>
#include <DXGame/FilePath.h>
#include <DXGame/DirectXTex/Texture.h>


// �f�X�g���N�^
FileStorage::~FileStorage(void) {
}


// �e�N�X�`���[��ǂݍ���
ID3D11ShaderResourceView* FileStorage::LoadTexture(const std::string& fileName) {
    //----- �ϐ��錾
    ID3D11ShaderResourceView* ret = nullptr;

    //----- ���ɑ��݂��邩
    if (m_texture.find(fileName) == m_texture.end()) {
        //----- ���݂���
        ret = m_texture.find(fileName)->second;
    }
    else {
        //----- ���݂��Ȃ����ߓǂݍ���
        LoadTextureFromFile(std::string(FilePath::TEXTURE_PATH + fileName).c_str(), &ret);
        m_texture.emplace(fileName, ret);
    }

    //----- �ԋp
    return ret;
}


// ���f����ǂݍ���
Model FileStorage::LoadModel(const std::string& fileName, const float scale, const bool flip) {
    //----- �ϐ��錾
    Model ret;

    //----- ���ɑ��݂��邩
    if (m_model.find(fileName) == m_model.end()) {
        //----- ���݂���
        ret = m_model.find(fileName)->second;
    }
    else {
        //----- ���݂��Ȃ����ߓǂݍ���
        ret.Load(std::string(FilePath::MODEL_PATH + fileName).c_str(), scale, flip);
        m_model.emplace(fileName, ret);
    }

    //----- �ԋp
    return ret;
}


// �R���X�g���N�^
FileStorage::FileStorage(void) {
}
