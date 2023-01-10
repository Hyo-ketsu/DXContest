#include <DXGame/GameObjectUpdater.h>
#include <DXGame/SystemDefines.h>


// �R���X�g���N�^
GameUpdater::GameUpdater(void) { 
    //----- ��s�m��
    m_gameObject.reserve(1024);   // ��芸����1024�m�ۂ���

    //----- �u�����h�X�e�[�g
    m_blendState = std::make_unique<std::remove_reference_t<decltype(*m_blendState.get())>>(BlendState());
    D3D11_RENDER_TARGET_BLEND_DESC blend = {};
    blend.BlendEnable           = TRUE;
    blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    blend.SrcBlend              = D3D11_BLEND_SRC_ALPHA;
    blend.SrcBlendAlpha         = D3D11_BLEND_ONE;
    blend.DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
    blend.DestBlendAlpha        = D3D11_BLEND_ONE;
    blend.BlendOp               = D3D11_BLEND_OP_ADD;
    blend.BlendOpAlpha          = D3D11_BLEND_OP_ADD;
    m_blendState->Create(blend);
    m_blendState->Bind();
}
// �f�X�g���N�^
GameUpdater::~GameUpdater(void) {
    //----- �폜�I�u�W�F�N�g�폜
    DeleteGameObject();

    //----- �S�폜
    for (auto& it : m_gameObject) {
        if (it == nullptr) continue;
        it->DeleteGameObject();
    }

    //----- �폜�I�u�W�F�N�g�폜
    DeleteGameObject();
}


// �X�V�������s��
void GameUpdater::Update(void) {
    //----- �폜�m�F
    DeleteGameObject();

    //----- �������������s��
    for (auto& it : m_gameObject) {
        it->Start();
    }

    //----- �폜�m�F
    DeleteGameObject();

    //----- �X�V�������s��
    for (auto& it : m_gameObject) {
        it->Update();
    }

    //----- �폜�m�F
    DeleteGameObject();

    //----- ��X�V�������s��
    for (auto& it : m_gameObject) {
        it->LateUpdate();
    }

    //----- �폜�m�F
    DeleteGameObject();
    
    //----- �����蔻������
    for (auto& it : m_gameObject) {
        if (it->GetCollsionEnable()) continue;
        it->ResetCollsionData();
        for (auto& targetIt : m_gameObject) {
            if (targetIt->GetCollsionEnable()) continue;
            it->UpdateCollsion(&*targetIt);
        }
    }

    //----- �����蔻�菈��
    for (auto& it : m_gameObject) {
        it->CollsionUpdate();
    }

    //----- �폜�m�F
    DeleteGameObject();
}
// �`�揈�����s��
void GameUpdater::Draw(void) { 
    //----- �`�揈�����s��
    for (auto& it : m_gameObject) {
        it->Draw();
        m_blendState->Bind();
    }
}


// �Q�[���I�u�W�F�N�g��ǉ�����
void GameUpdater::AddGameObject(GameObject* gameObject) { 
    m_gameObject.push_back(std::unique_ptr<std::remove_reference<decltype(*m_gameObject.front().get())>::type>(gameObject));
    gameObject->CreatePrefab();
}
// �Q�[���I�u�W�F�N�g���폜����
const bool GameUpdater::DeleteGameObject(GameObject* gameObject) {
    //----- ����
    for (int i = 0; i < m_gameObject.size(); i++) {
        if (m_gameObject[i].get() == gameObject) {
            //----- ���Q�[���I�u�W�F�N�g�B����
            gameObject->SetActive(false);
            m_deleteIndex.push_back(i);
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


// �폜�C���f�b�N�X�ɓo�^����Ă���Q�[���I�u�W�F�N�g�̏���
void GameUpdater::DeleteGameObject(void) {
    //----- �폜�I�u�W�F�N�g�����邩
    if (m_deleteIndex.empty()) return;

    //----- �ϐ��錾
    std::list<unsigned int> deleteIndex; // �~���Ƀ\�[�g����d���̔r�����ꂽ�폜�C���f�b�N�X

    //----- �擪�f�[�^�}��
    deleteIndex.push_back(m_deleteIndex.front());

    //----- �폜�C���f�b�N�X�\�[�g
    // Memo : �����}���\�[�g���s���Ă��܂�
    // Memo : �~���Ƀ\�[�g���s���܂�
    // Memo : �d����r�����܂�
    for (auto index : m_deleteIndex) {
        //----- �v�f�Ƃ̔�r
        for (auto it = deleteIndex.begin();; it++) { // �������͎���if���ɂ�
            //----- ���ݒl���I�[�i�ǂ̒l��菬�����j�Ȃ疖���ɒǉ��B���̓��͒l�̔�r�Ɉڂ�
            if (it == deleteIndex.end()) {
                deleteIndex.push_back(index);   // �����ɒǉ�
                break;  // �}���A�l�Ƃ̔�r����߁A���̓��͒l�̔�r�Ɉڂ�
            }

            //----- ���͒l�����ݒl���傫���ꍇ�͑}��
            if (index > *it) {
                deleteIndex.insert(it, index);
                break;  // �}���A�l�Ƃ̔�r����߁A���̓��͒l�̔�r�Ɉڂ�
            }

            //----- ���͒l�����ݒl�Ɠ����Ȃ��r����߂�i���}�����Ȃ��j
            if (index == *it) {
                break;  // �l�Ƃ̔�r����߁A���̓��͒l�̔�r�Ɉڂ�
            }
        }
    }

    //----- �Q�[���I�u�W�F�N�g�폜
    for (auto index : deleteIndex) {
        m_gameObject[index].reset();
        m_gameObject.erase(m_gameObject.begin() + index);
    }
    m_deleteIndex.clear();
}
