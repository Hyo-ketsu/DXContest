#include <DXGame/Scene.h>
#include <DXGame/GameObjectUpdater.h>


// コンストラクタ
SceneBase::SceneBase(void) 
    : m_updater(std::make_unique<std::remove_reference<decltype(*m_updater.get())>::type>()){
}
// デストラクタ
SceneBase::~SceneBase(void) {
}
