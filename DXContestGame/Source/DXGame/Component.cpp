#include <DXGame/Component.h>


// コンストラクタ
Component::Component(GameObject* gameObject)
    : m_isActive(true)
    , m_gameObject(gameObject) {
}
