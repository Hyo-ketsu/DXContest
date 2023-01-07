#include <DXGame/FileStorage.h>
#include <DXGame/FilePath.h>
#include <DXGame/DirectXTex/Texture.h>
#include <DXGame/Utility.h>


// �f�X�g���N�^
FileStorage::~FileStorage(void) {
}


// �e�N�X�`���[��ǂݍ���
ID3D11ShaderResourceView* FileStorage::LoadTexture(const std::string& fileName) {
    //----- �ϐ��錾
    ID3D11ShaderResourceView* ret = nullptr;

    //----- ���ɑ��݂��邩
    if (m_texture.find(fileName) != m_texture.end()) {
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
Model* FileStorage::LoadModel(const std::string& fileName, const float scale, const bool flip) {
    ////----- ���ɑ��݂��邩
    //if (m_model.find(fileName) != m_model.end()) {
    //    //----- ���݂���
    //    return new Model(*m_model.find(fileName)->second.get());
    //}
    //else {
    //    //----- ���݂��Ȃ����ߓǂݍ���
    //    Model* model = new Model();
    //    model->Load(std::string(FilePath::MODEL_PATH + fileName), scale, flip);
    //    m_model.emplace(fileName, std::unique_ptr<Model>(model));
    //    return new Model(*m_model.find(fileName)->second.get());
    //}

    Model* model = new Model();
    model->Load(std::string(FilePath::MODEL_PATH + fileName), scale, flip);
    return model;
}


// �R���X�g���N�^
FileStorage::FileStorage(void) {
}
