#include <DXGame/FileStorage.h>
#include <DXGame/FilePath.h>
#include <DXGame/DirectXTex/Texture.h>
#include <DXGame/Utility.h>
#include <DXGame/SceneLoader.h>


// �f�X�g���N�^
FileStorage::~FileStorage(void) {
    SceneLoader::Get()->DeleteInstance();
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
        LoadTextureFromFile(Utility::MergeString(FilePath::TEXTURE_PATH, fileName).c_str(), &ret);
        m_texture.emplace(fileName, ret);
    }

    //----- �ԋp
    return ret;
}


// ���f����ǂݍ���
Model* const FileStorage::LoadModel(const std::string& fileName, const float scale, const bool flip) {
    //----- ���b�N
    m_modelMutex.lock();
    
    //----- �ϐ��錾
    auto data = m_model.find(fileName);
    
    //----- ���f�������邩�i����΃��f�����擾���ĕԋp����j
    for (; data != m_model.end(); data++) {
        //----- �g�p�ς݂�
        if (data->second.first == false) {
            //----- �g���Ă��Ȃ��B���̃��f�����g�p
            data->second.first = true;          // �g�p�ς݂Ƃ���
            return data->second.second.get();
        }
    }

    //----- ���f�����Ȃ��B�ǂݍ���Œǉ�
    Model* model = new Model();
    // ��s����"�g�p�ς�"�Ƃ��Ēǉ��i�ǂݍ��݌�ɊJ������j
    auto it = m_model.emplace(std::pair<std::string, std::pair<UseModel, std::unique_ptr<Model>>>(
        fileName, std::pair<UseModel, std::unique_ptr<Model>>(true, std::unique_ptr<Model>(model))
        )
    );

    //----- ���b�N����
    m_modelMutex.unlock();

    //----- ���f���ǂݍ���
    model->Load(std::string(FilePath::MODEL_PATH + fileName), scale, flip);

    //----- ���b�N
    std::scoped_lock<std::recursive_mutex> lock(m_modelMutex);

    // �ǂݍ��݊����B"���g�p"�Ƃ��ĊJ��
    it->second.first = false;

    //----- �ԋp
    return model;
}


// �g�p�������f����ԋp����
void FileStorage::ReturnModel(const Model* const model) {
    //----- ���|�C���^�̃��f��������
    for (auto& it : m_model) {
        if (it.second.second.get() == model) {
            //----- ���|�C���^�̃��f���B�g�p�ς݂��J������
            it.second.first = false;
        }
    }
}


// �R���X�g���N�^
FileStorage::FileStorage(void) {
}
