#include <DXGame/SceneLoader.h>
#include <DXGame/DirectX.h>


// �f�X�g���N�^
SceneLoader::~SceneLoader(void) {
    DeleteScene();
}
// �R���X�g���N�^
SceneLoader::SceneLoader(void)
    : m_scene(nullptr) {
}


// ���݃V�[�����擾����
SceneBase* const SceneLoader::GetScene(void) const {
    return m_scene ? m_scene.get() : nullptr; // ���݂̃V�[�����ݒ肳��Ă���΂���̃|�C���^�A�����łȂ���� nullptr
}


// �V�[�����폜����
void SceneLoader::DeleteScene(void) {
    m_scene.reset();
}


// �X�V�������s��
void SceneLoader::Update(void) {
    m_scene->GetUpdater()->Update();
}
// �`�揈�����s��
void SceneLoader::Draw(void) {
    //----- �O�`�揈��
    BeginDrawDX();

    //----- �`�揈��
    m_scene->GetUpdater()->Draw();

    //----- ��`�揈��
    EndDrawDX();
}