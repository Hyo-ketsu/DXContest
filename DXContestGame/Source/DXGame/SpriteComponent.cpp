#include <DXGame/SpriteComponent.h>
#include <DXGame/FileStorage.h>
#include <DXGame/Sprite.h>


// �R���X�g���N�^
SpriteShowComponent::SpriteShowComponent(GameObject* gameObject, const std::string& file)
    : Component(gameObject)
    , m_fileName(file)
    , m_sprite(nullptr) {
}


void SpriteShowComponent::Start(void) {
    //----- �X�v���C�g�ǂݍ���
    m_sprite = FileStorage::Get()->LoadTexture(m_fileName);
}
void SpriteShowComponent::Draw(void) {
    //----- �P�ʍs��ݒ�
    DirectX::XMFLOAT4X4 float4x4;
    DirectX::XMStoreFloat4x4(&float4x4, DirectX::XMMatrixIdentity());
    Sprite::SetWorld(float4x4);
    Sprite::SetView(float4x4);
    Sprite::SetProjection(float4x4);

    //----- �e�N�X�`���ݒ�
    Sprite::SetSize({ m_gameObject->GetTransform().size.x,m_gameObject->GetTransform().size.y });
    Sprite::SetOffset({ m_gameObject->GetTransform().pos.x, m_gameObject->GetTransform().pos.y });
    Sprite::SetTexture(m_sprite);
    Sprite::Draw();
}
