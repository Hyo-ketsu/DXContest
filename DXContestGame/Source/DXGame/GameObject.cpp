#include <DXGame/GameObject.h>
#include <DXGame/Component.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/Scene.h>


// �R���X�g���N�^
GameObject::GameObject(SceneBase* scene, const Transform& transform)
    : m_isActive(true)
    , m_isCreatePrefab(false)
    , m_name(DEFAULT_NAME_GAMEOBJECT)
    , m_transform(transform)
    , m_oldTransform(transform)
    , m_scene(scene) {
}
// �f�X�g���N�^
GameObject::~GameObject(void) {
}


// �R���|�[�l���g�̏������������s��
void GameObject::Start(void) {
    //----- ���������������ׂẴR���|�[�l���g�ɍs��
    for (auto& it : m_component) {
        if (it->GetInit() == false) {   // ���������s���Ă��Ȃ���΃A�N�e�B�u�֌W�Ȃ��ɏ������������s��
            it->GameObjectStart();
        }
    }
}
// �R���|�[�l���g�̍X�V�������s��
void GameObject::Update(void) {
    //----- �Q�[���I�u�W�F�N�g���g���L���łȂ���Ώ������̂��X�L�b�v����
    if (m_isActive == false) return;

    //----- �X�V���������ׂẴR���|�[�l���g�ɍs��
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // �A�N�e�B�u�����������s���Ă���΍X�V�������s��
            it->Update();
        }
    }
}
// �R���|�[�l���g�̌�X�V�������s��
void GameObject::LateUpdate(void) {
    //----- �Q�[���I�u�W�F�N�g���g���L���łȂ���Ώ������̂��X�L�b�v����
    if (m_isActive == false) return;

    //----- ��X�V���������ׂẴR���|�[�l���g�ɍs��
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // �A�N�e�B�u�����������s���Ă���Ό�X�V�������s��
            it->LateUpdate();
        }
    }

    //----- �ߋ����W�̍X�V
    m_oldTransform = m_transform;
}
// �R���|�[�l���g�̕`�揈�����s��
void GameObject::Draw(void) {
    //----- �Q�[���I�u�W�F�N�g���g���L���łȂ���Ώ������̂��X�L�b�v����
    if (m_isActive == false) return;

    //----- �`�揈�������ׂẴR���|�[�l���g�ɍs��
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // �A�N�e�B�u�����������s���Ă���Ε`�揈�����s��
            it->Draw();
        }
    }
}
// �R���|�[�l���g�̓����蔻�菈�����s��
void GameObject::CollsionUpdate(void) {
    //----- �Q�[���I�u�W�F�N�g���g���L���łȂ���Ώ������̂��X�L�b�v����
    if (m_isActive == false) return;

    //----- �`�揈�������ׂẴR���|�[�l���g�ɍs��
    for (auto& it : m_component) {
        if (it->GetInit() && it->GetActive()) { // �A�N�e�B�u�����������s���Ă���Ε`�揈�����s��
            it->Collsion();
        }
    }
}


// �v���n�u�𐶐�����
const bool GameObject::CreatePrefab(void) {
    //----- ��������
    if (m_isCreatePrefab == false) {
        //----- ��������Ă��Ȃ��B�v���n�u�������s��
        m_isCreatePrefab = true;
        Prefab();
        return true;
    }

    //----- ���ɐ�������Ă���
    return false;
}


// �Q�[���I�u�W�F�N�g����
void GameObject::DeleteGameObject(void) {
    m_scene->GetUpdater()->DeleteGameObject(this);
}


// �R���|�[�l���g��ǉ�����
Component* GameObject::AddComponent(Component* component)
{
    m_component.push_back(std::unique_ptr<Component>(component));
    return m_component.back().get();
}
// �����蔻���ǉ�����
Collsion* GameObject::AddCollsion(const bool isHitMove, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& pos) {
    m_collsion.push_back(std::unique_ptr<Collsion>(new Collsion(this, isHitMove, size, pos)));
    return m_collsion.back().get();
}


// �����蔻������
void GameObject::UpdateCollsion(GameObject* const gameObject) {
    //----- ���g�ƑΏۂ�Collsion�œ����蔻������
    for (auto& it : m_collsion) {
        for (auto& targetIt : gameObject->m_collsion) {
            //----- �����蔻����Ƃ�
            auto next = it->CollsionHitCheck(targetIt.get());

            //----- ����Ƀx�N�g�����g���������蔻����s�����i�����ړ��ɑΉ����������蔻��j
        }
    }
}
// �����蔻�肪���݂��邩
const bool GameObject::GetCollsionEnable(void) const {
    return m_collsion.empty();
}
// �����蔻�胊�X�g�̏���
void GameObject::ResetCollsionData(void) {
    m_collsionData.list.clear();
}
