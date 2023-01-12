#include <DXGame/ButtonComponent.h>
#include <DXGame/FileStorage.h>
#include <DXGame/Input.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SpriteComponent.h>


// �R���X�g���N�^
ButtonBase::ButtonBase(GameObject* gameObject, const std::string& file) 
    : Component(gameObject) {
    auto* sprite = new SpriteShowComponent(gameObject, file);
    m_gameObject->AddComponent(sprite);
}


void ButtonBase::Update(void) {
    if (IsKeyPress(KEY_BUTTON)) {
        this->ButtonPush();
    }
}
