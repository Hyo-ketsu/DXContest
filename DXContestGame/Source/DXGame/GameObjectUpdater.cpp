#include <DXGame/GameObjectUpdater.h>
#include <DXGame/SystemDefines.h>


// �R���X�g���N�^
GameUpdater::GameUpdater(void) { 
    m_gameObject.resize(256);   // ��芸����256�m�ۂ���
}
// �f�X�g���N�^
GameUpdater::~GameUpdater(void) { 
}


// �X�V�������s��
void GameUpdater::Update(void) { 
    //----- �������������s��
    for (auto& it : m_gameObject) {
        it->Start();
    }

    //----- �X�V�������s��
    for (auto& it : m_gameObject) {
        it->Update();
    }

    //----- ��X�V�������s��
    for (auto& it : m_gameObject) {
        it->LateUpdate();
    }
}
// �`�揈�����s��
void GameUpdater::Draw(void) { 
    //----- �`�揈�����s��
    for (auto& it : m_gameObject) {
        it->Draw();
    }
}


// �Q�[���I�u�W�F�N�g��ǉ�����
void GameUpdater::AddGameObject(GameObject* gameObject) { 
    m_gameObject.push_back(std::unique_ptr<std::remove_reference<decltype(*m_gameObject.front().get())>::type>(gameObject));
}
// �Q�[���I�u�W�F�N�g���폜����
const bool GameUpdater::DeleteGameObject(GameObject* gameObject) {
    //----- ����
    for (auto it = m_gameObject.begin(); it != m_gameObject.end(); it++) {
        if (it->get() == gameObject) {
            //----- �����Q�[���I�u�W�F�N�g�B����
            m_gameObject.erase(it);
            return true;
        }
    }

    //----- ���݂��Ȃ����ߏ������s
    return false;
}


// �Q�[���I�u�W�F�N�g�𖼑O��������
GameObject* GameUpdater::FindGameObject(const std::string& name) const {
    //----- �f�t�H���g�l�[���ł���Ό������̂����Ȃ�
    if (name == DEFAULT_NAME_GAMEOBJECT) return nullptr;

    //----- ����
    for (auto& it : m_gameObject) {
        if (it->GetName() == name) {
            //----- �����Q�[���I�u�W�F�N�g���B�ԋp
            return &*it;
        }
    }

    //----- �����Q�[���I�u�W�F�N�g�����݂��Ȃ�
    return nullptr;
}
