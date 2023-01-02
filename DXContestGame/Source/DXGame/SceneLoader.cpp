#include <DXGame/SceneLoader.h>


// �f�X�g���N�^
SceneLoader::~SceneLoader(void) {
    UninitGameUpdater();
}


// �R���X�g���N�^
SceneLoader::SceneLoader(void)
    : m_gameUpdater(nullptr)
    , m_currentScene(nullptr) {
    InitGameUpdater();
}


// ���݃V�[�����擾����
SceneBase* SceneLoader::GetScene(void) {
    return m_currentScene ? m_currentScene.get() : nullptr; // ���݂̃V�[�����ݒ肳��Ă���΂���̃|�C���^�A�����łȂ���� nullptr
}


// �Q�[���A�b�v�f�[�^�[������
void SceneLoader::InitGameUpdater(void) {
    m_gameUpdater = std::make_unique<std::remove_reference<decltype(*m_gameUpdater.get())>::type>();
}
// �Q�[���A�b�v�f�[�^�[�I��
void SceneLoader::UninitGameUpdater(void) {
    m_gameUpdater.reset();
}


// �Q�[���A�b�v�f�[�^�[���擾����
GameUpdater& SceneLoader::GetGameUpdaterRef(void) {
    if (m_gameUpdater) {
        //----- ���݂���B���̂܂ܕԋp
        return *m_gameUpdater.get();
    }
    else {
        //----- ���݂��Ȃ��B��O�𓊂���
        throw std::logic_error("Exception! Value 'm_gameUpdater' not initialized");
    }
}
