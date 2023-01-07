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
void GameObject::AddComponent(Component* component)
{
    m_component.push_back(std::unique_ptr<Component>(component));
}
