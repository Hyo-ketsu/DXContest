#include <DXGame/Number.h>
#include <DXGame/FileStorage.h>
#include <array>


#if 1
const unsigned int NUMBER_DIGIT     = 7;        // �����\���̌���
const float NUMBER_DEFAULT_DISTANCE = 0.075f;   // �\���Ԋu�f�t�H���g
const unsigned int NUMBER_SPRITE_SPRITE_X = 10; // ��������
const unsigned int NUMBER_SPRITE_SPRITE_Y = 1;  // �c������
const std::string NUMBER_TEXTURE_FILENAME_0 = "Number0.png";
const std::string NUMBER_TEXTURE_FILENAME_1 = "Number1.png";
const std::string NUMBER_TEXTURE_FILENAME_2 = "Number2.png";
const std::string NUMBER_TEXTURE_FILENAME_3 = "Number3.png";
const std::string NUMBER_TEXTURE_FILENAME_4 = "Number4.png";
const std::string NUMBER_TEXTURE_FILENAME_5 = "Number5.png";
const std::string NUMBER_TEXTURE_FILENAME_6 = "Number6.png";
const std::string NUMBER_TEXTURE_FILENAME_7 = "Number7.png";
const std::string NUMBER_TEXTURE_FILENAME_8 = "Number8.png";
const std::string NUMBER_TEXTURE_FILENAME_9 = "Number9.png";


// �R���X�g���N�^
NumberShow::NumberShow(GameObject* gameObject) 
    : Component(gameObject)
    , m_number(0)
    , m_showDistance(NUMBER_DEFAULT_DISTANCE) {
}


void NumberShow::Start(void) {
    m_texture0 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_0);
    m_texture1 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_1);
    m_texture2 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_2);
    m_texture3 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_3);
    m_texture4 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_4);
    m_texture5 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_5);
    m_texture6 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_6);
    m_texture7 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_7);
    m_texture8 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_8);
    m_texture9 = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME_9);
}
void NumberShow::Draw(void) {
    //----- �ϐ��錾
    std::array<unsigned short, NUMBER_DIGIT> showNumber;    // �\���p���l��ێ����Ă����ϐ��i�㌅����i�[�j
    unsigned int number = m_number;    // �v�Z�p���l

    //----- �\���p���l�Z�o
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        showNumber.at(i) = number % 10;
        number /= 10;
    }

    //----- �\���p���l�t�]
    // ����������[���Ă����̂��㌅�ɕύX���܂�
    for (int i = 0; i < NUMBER_DIGIT / 2; i++) {
        unsigned int work = showNumber.at(i);
        showNumber.at(i) = showNumber.at(NUMBER_DIGIT - 1 - i); // -1 ��0�C���f�b�N�X�ɍ��킹�邽��
        showNumber.at(NUMBER_DIGIT - 1 - i) = work;
    }

    //----- �`��p�ϐ��錾
    const DirectX::XMFLOAT2 pos = { m_gameObject->GetTransform().pos.x,m_gameObject->GetTransform().pos.y };    // ���ݍ��W

    //----- �`�揀��
    // 2D�p�s��ݒ�
    DirectX::XMFLOAT4X4 float4x4;
    DirectX::XMStoreFloat4x4(&float4x4, DirectX::XMMatrixIdentity());
    Sprite::SetWorld(float4x4);
    Sprite::SetView(float4x4);
    Sprite::SetProjection(float4x4);
    // UV���ݒ�
    Sprite::SetSize({ m_gameObject->GetTransform().size.x,m_gameObject->GetTransform().size.y });

    //----- �`��
    int i = 0;
    for (auto it : showNumber) {
        Sprite::SetOffset({ pos.x + i * NUMBER_DEFAULT_DISTANCE ,pos.y });
        switch (it) {
        case 0: Sprite::SetTexture(m_texture0); break;
        case 1: Sprite::SetTexture(m_texture1); break;
        case 2: Sprite::SetTexture(m_texture2); break;
        case 3: Sprite::SetTexture(m_texture3); break;
        case 4: Sprite::SetTexture(m_texture4); break;
        case 5: Sprite::SetTexture(m_texture5); break;
        case 6: Sprite::SetTexture(m_texture6); break;
        case 7: Sprite::SetTexture(m_texture7); break;
        case 8: Sprite::SetTexture(m_texture8); break;
        case 9: Sprite::SetTexture(m_texture9); break;
        }
        Sprite::Draw();
        i++;
    }
}
#endif


#if 0
// ���ŁBUV�Ŏ���
const unsigned int NUMBER_DIGIT     = 7;    // �����\���̌���
const float NUMBER_DEFAULT_DISTANCE = 3;    // �\���Ԋu�f�t�H���g
const unsigned int NUMBER_SPRITE_SPRITE_X = 10; // ��������
const unsigned int NUMBER_SPRITE_SPRITE_Y = 1;  // �c������
const std::string NUMBER_TEXTURE_FILENAME = "Number.png";


// �R���X�g���N�^
NumberShow::NumberShow(GameObject* gameObject) 
    : Component(gameObject)
    , m_number(0)
    , m_showDistance(NUMBER_DEFAULT_DISTANCE) {
}


void NumberShow::Start(void) {
    m_texture = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME);
}
void NumberShow::Draw(void) {
    //----- �ϐ��錾
    std::array<unsigned short, NUMBER_DIGIT> showNumber;    // �\���p���l��ێ����Ă����ϐ��i�㌅����i�[�j
    unsigned int number = m_number;    // �v�Z�p���l

    //----- �\���p���l�Z�o
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        showNumber.at(i) = number % 10;
        number /= 10;
    }

    //----- �\���p���l�t�]
    // ����������[���Ă����̂��㌅�ɕύX���܂�
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        unsigned int work = showNumber.at(i);
        showNumber.at(i) = showNumber.at(NUMBER_DIGIT - 1 - i); // -1 ��0�C���f�b�N�X�ɍ��킹�邽��
        showNumber.at(NUMBER_DIGIT - 1 - i) = work;
    }

    //----- �`��p�ϐ��錾
    const DirectX::XMFLOAT2 pos = { m_gameObject->GetTransform().pos.x,m_gameObject->GetTransform().pos.y };    // ���ݍ��W
    const DirectX::XMFLOAT2 uvSize = { 1.f / NUMBER_SPRITE_SPRITE_X,1.f / NUMBER_SPRITE_SPRITE_Y };

    //----- �`�揀��
    // �e�N�X�`���ݒ�
    Sprite::SetTexture(m_texture);
    // 2D�p�s��ݒ�
    DirectX::XMFLOAT4X4 float4x4;
    DirectX::XMStoreFloat4x4(&float4x4, DirectX::XMMatrixIdentity());
    Sprite::SetWorld(float4x4);
    Sprite::SetView(float4x4);
    Sprite::SetProjection(float4x4);
    // UV���ݒ�
    Sprite::SetSize({ m_gameObject->GetTransform().size.x,m_gameObject->GetTransform().size.y });
    Sprite::SetOffset(pos);
    Sprite::SetUVScale(uvSize);

    //----- �`��
    int i = 0;
    for (auto it : showNumber) {
        Sprite::SetOffset({ pos.x + i * m_gameObject->GetTransform().size.x ,pos.y });
        Sprite::SetUVPos({ it % NUMBER_SPRITE_SPRITE_X * uvSize.x,it / NUMBER_SPRITE_SPRITE_X * uvSize.y });
        Sprite::Draw();
        i++;
    }
}
#endif
