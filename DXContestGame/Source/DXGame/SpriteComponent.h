#ifndef _____SPRITECOMPONENT_H____
#define _____SPRITECOMPONENT_H____

#include <DXGame/GameObject.h>


class SpriteShowComponent : public Component {
public:
    // コンストラクタ
    // @ Arg1 : ゲームオブジェクト
    // @ Arg2 : スプライトファイル名
    SpriteShowComponent(GameObject* gameObject, const std::string& file);


    // 色ゲッター
    const DirectX::XMFLOAT4 GetColor(void) const { return m_color; }
    // 色セッター
    void SetColor(const DirectX::XMFLOAT4& in) { m_color = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    const std::string         m_fileName;   // ファイル読み込み、
    ID3D11ShaderResourceView* m_sprite;     // 表示スプライト
    DirectX::XMFLOAT4         m_color;      // 色
};


#endif // !_____SPRITECOMPONENT_H____
