#include <DXGame/MenuButtonSelector.h>
#include <DXGame/SpriteComponent.h>
#include <DXGame/GameDefine.h>
#include <DXGame/Input.h>
#include <DXGame/SceneLoader.h>


void MenuGameObjectClient::Start(void) {
    //----- ���j���[�V�X�e���Ɏ����I�ɒǉ�����
    SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_MENU)->GetComponent<MenuGameObjectControl>()->AddGameObject(m_gameObject);
}


void MenuGameObjectControl::Start(void) {
    m_currentCursor = 0;
}
void MenuGameObjectControl::Update(void) {
    //----- ���W�ݒ�
    if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
        //----- �͈͊O�B�������Ȃ�
    }
    else {
        //----- �͈͓��B�w��C���f�b�N�X��
    }

    //----- �㉺�I��
    if (IsKeyTrigger('W') || IsKeyTrigger(VK_UP)) {
        if (m_currentCursor > 0) {
            m_gameObject->SetTransform(m_children[m_currentCursor]->GetTransform());
            m_currentCursor--;
        } 
    }
    if (IsKeyTrigger('S') || IsKeyTrigger(VK_DOWN)) {
        if (m_currentCursor < m_children.size() - 1) {
            m_gameObject->SetTransform(m_children[m_currentCursor]->GetTransform());
            m_currentCursor++;
        }
    }

    //----- ����
    if (IsKeyTrigger(KEY_BUTTON)) {
        //----- �͈͊O�`�F�b�N
        if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
            //----- �͈͊O�B�������Ȃ�
        }
        else {
            //----- �͈͓��B�֐������s����
            m_children[m_currentCursor]->GetComponent<MenuGameObjectClient>()->Action();
        }
    }

    //----- �ʒu�ݒ�
    if (m_currentCursor < 0 || m_currentCursor >= m_children.size()) {
        //----- �͈͊O�B�T�C�Y���[���ɂ��ĕ`�悵�Ȃ��悤�ɂ���
        m_gameObject->SetTransform(Transform({ 0,0,0 }, { 0,0,0 }));
    }
    else {
        //----- �͈͓��B�ʒu��ݒ肷��
        auto transofrm = m_children[m_currentCursor]->GetTransform();
        transofrm.pos.x  -= transofrm.size.x;
        transofrm.size.x /= 2;
        transofrm.pos.x  += transofrm.size.x / 2;
        m_gameObject->SetTransform(transofrm);
    }
}


// �Q�[���I�u�W�F�N�g��ǉ�����
void MenuGameObjectControl::AddGameObject(GameObject *gameObject) {
    //----- �N���C�A���g���ǉ�����Ă��邩
    if (gameObject->GetComponent<MenuGameObjectClient>() == nullptr) throw std::exception("Errer! MenuGameObjectClient not attached");

    //----- �Q�[���I�u�W�F�N�g�̒ǉ�
    m_children.push_back(gameObject);
}


void MenuGameObject::Prefab(void) {
    //----- �X�e�[�^�X�ݒ�
    SetName(NAME_MENU);
    SetTransform(Transform({ 0,0,0 }, { 0,0,0 }));

    //----- �R���|�[�l���g�̒ǉ�
    AddComponent<MenuGameObjectControl>();
    auto sprite = new SpriteShowComponent(this, LOAD_CURSOR_FILENAME);
    AddComponent(sprite);
}
