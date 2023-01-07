#include <DXGame/Component.h>


// コンストラクタ
Component::Component(GameObject* gameObject)
    : m_isActive(true)
    , m_isInit(false)
    , m_gameObject(gameObject) {
}


// ゲームオブジェクト用初期化処理
void Component::GameObjectStart(void) {
    if (m_isInit == false) {
        this->Start();
        m_isInit = true;
    }
}
