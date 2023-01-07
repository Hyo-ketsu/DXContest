#include <DXGame/Component.h>


// �R���X�g���N�^
Component::Component(GameObject* gameObject)
    : m_isActive(true)
    , m_isInit(false)
    , m_gameObject(gameObject) {
}


// �Q�[���I�u�W�F�N�g�p����������
void Component::GameObjectStart(void) {
    if (m_isInit == false) {
        this->Start();
        m_isInit = true;
    }
}
