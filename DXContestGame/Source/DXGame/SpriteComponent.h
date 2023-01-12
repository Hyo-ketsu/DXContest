#ifndef _____SPRITECOMPONENT_H____
#define _____SPRITECOMPONENT_H____

#include <DXGame/GameObject.h>


class SpriteShowComponent : public Component {
public:
    // コンストラクタ
    // @ Arg1 : ゲームオブジェクト
    // @ Arg2 : スプライトファイル名
    SpriteShowComponent(GameObject* gameObject, const std::string& file);


    void Start(void) override;
    void Draw(void) override;

private:
    const std::string         m_fileName;   // ファイル読み込み、
    ID3D11ShaderResourceView* m_sprite;     // 表示スプライト
};


#endif // !_____SPRITECOMPONENT_H____
