#include <DXGame/Component.h>


// �R���X�g���N�^
Component::Component(GameObject* gameObject)
    : m_isActive(true)
    , m_gameObject(gameObject) {
}
