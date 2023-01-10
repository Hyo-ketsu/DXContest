#include <DXGame/Number.h>
#include <DXGame/FileStorage.h>
#include <array>


#if 1
const unsigned int NUMBER_DIGIT     = 7;        // 数字表示の桁数
const float NUMBER_DEFAULT_DISTANCE = 0.075f;   // 表示間隔デフォルト
const unsigned int NUMBER_SPRITE_SPRITE_X = 10; // 横分割数
const unsigned int NUMBER_SPRITE_SPRITE_Y = 1;  // 縦分割数
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


// コンストラクタ
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
    //----- 変数宣言
    std::array<unsigned short, NUMBER_DIGIT> showNumber;    // 表示用数値を保持しておく変数（上桁から格納）
    unsigned int number = m_number;    // 計算用数値

    //----- 表示用数値算出
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        showNumber.at(i) = number % 10;
        number /= 10;
    }

    //----- 表示用数値逆転
    // 下桁から収納していたのを上桁に変更します
    for (int i = 0; i < NUMBER_DIGIT / 2; i++) {
        unsigned int work = showNumber.at(i);
        showNumber.at(i) = showNumber.at(NUMBER_DIGIT - 1 - i); // -1 は0インデックスに合わせるため
        showNumber.at(NUMBER_DIGIT - 1 - i) = work;
    }

    //----- 描画用変数宣言
    const DirectX::XMFLOAT2 pos = { m_gameObject->GetTransform().pos.x,m_gameObject->GetTransform().pos.y };    // 現在座標

    //----- 描画準備
    // 2D用行列設定
    DirectX::XMFLOAT4X4 float4x4;
    DirectX::XMStoreFloat4x4(&float4x4, DirectX::XMMatrixIdentity());
    Sprite::SetWorld(float4x4);
    Sprite::SetView(float4x4);
    Sprite::SetProjection(float4x4);
    // UV等設定
    Sprite::SetSize({ m_gameObject->GetTransform().size.x,m_gameObject->GetTransform().size.y });

    //----- 描画
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
// 旧版。UVで死ぬ
const unsigned int NUMBER_DIGIT     = 7;    // 数字表示の桁数
const float NUMBER_DEFAULT_DISTANCE = 3;    // 表示間隔デフォルト
const unsigned int NUMBER_SPRITE_SPRITE_X = 10; // 横分割数
const unsigned int NUMBER_SPRITE_SPRITE_Y = 1;  // 縦分割数
const std::string NUMBER_TEXTURE_FILENAME = "Number.png";


// コンストラクタ
NumberShow::NumberShow(GameObject* gameObject) 
    : Component(gameObject)
    , m_number(0)
    , m_showDistance(NUMBER_DEFAULT_DISTANCE) {
}


void NumberShow::Start(void) {
    m_texture = FileStorage::Get()->LoadTexture(NUMBER_TEXTURE_FILENAME);
}
void NumberShow::Draw(void) {
    //----- 変数宣言
    std::array<unsigned short, NUMBER_DIGIT> showNumber;    // 表示用数値を保持しておく変数（上桁から格納）
    unsigned int number = m_number;    // 計算用数値

    //----- 表示用数値算出
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        showNumber.at(i) = number % 10;
        number /= 10;
    }

    //----- 表示用数値逆転
    // 下桁から収納していたのを上桁に変更します
    for (int i = 0; i < NUMBER_DIGIT; i++) {
        unsigned int work = showNumber.at(i);
        showNumber.at(i) = showNumber.at(NUMBER_DIGIT - 1 - i); // -1 は0インデックスに合わせるため
        showNumber.at(NUMBER_DIGIT - 1 - i) = work;
    }

    //----- 描画用変数宣言
    const DirectX::XMFLOAT2 pos = { m_gameObject->GetTransform().pos.x,m_gameObject->GetTransform().pos.y };    // 現在座標
    const DirectX::XMFLOAT2 uvSize = { 1.f / NUMBER_SPRITE_SPRITE_X,1.f / NUMBER_SPRITE_SPRITE_Y };

    //----- 描画準備
    // テクスチャ設定
    Sprite::SetTexture(m_texture);
    // 2D用行列設定
    DirectX::XMFLOAT4X4 float4x4;
    DirectX::XMStoreFloat4x4(&float4x4, DirectX::XMMatrixIdentity());
    Sprite::SetWorld(float4x4);
    Sprite::SetView(float4x4);
    Sprite::SetProjection(float4x4);
    // UV等設定
    Sprite::SetSize({ m_gameObject->GetTransform().size.x,m_gameObject->GetTransform().size.y });
    Sprite::SetOffset(pos);
    Sprite::SetUVScale(uvSize);

    //----- 描画
    int i = 0;
    for (auto it : showNumber) {
        Sprite::SetOffset({ pos.x + i * m_gameObject->GetTransform().size.x ,pos.y });
        Sprite::SetUVPos({ it % NUMBER_SPRITE_SPRITE_X * uvSize.x,it / NUMBER_SPRITE_SPRITE_X * uvSize.y });
        Sprite::Draw();
        i++;
    }
}
#endif
