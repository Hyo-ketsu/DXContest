#include <DXGame/Scene.h>
#include <DXGame/GameObjectUpdater.h>


// �R���X�g���N�^
SceneBase::SceneBase(void) 
    : m_updater(std::make_unique<std::remove_reference<decltype(*m_updater.get())>::type>()){
}
// �f�X�g���N�^
SceneBase::~SceneBase(void) {
}
