#ifndef ____NUMBER_H____
#define ____NUMBER_H____

#include <DXGame/Sprite.h>
#include <DXGame/GameObject.h>
#include <DXGame/BlendState.h>
#include <DXGame/BlendState.h>


#if 1
// 数字を表示する
// @ Memo : 生成位置から右に表示します
class NumberShow : public Component {
public:
    // コンストラクタ
    // @ Arg1 : ゲームオブジェクト
    NumberShow(GameObject* gameObject);

    // 数字セッター
    void SetNumber(const unsigned int in) { m_number = in; }

    // 表示間隔セッター
    void SetShowDistance(const float in) { m_showDistance = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    unsigned int m_number;                  // 表示する数字
    float        m_showDistance;            // 表示間隔
    ID3D11ShaderResourceView* m_texture0;   // Texture
    ID3D11ShaderResourceView* m_texture1;   // Texture
    ID3D11ShaderResourceView* m_texture2;   // Texture
    ID3D11ShaderResourceView* m_texture3;   // Texture
    ID3D11ShaderResourceView* m_texture4;   // Texture
    ID3D11ShaderResourceView* m_texture5;   // Texture
    ID3D11ShaderResourceView* m_texture6;   // Texture
    ID3D11ShaderResourceView* m_texture7;   // Texture
    ID3D11ShaderResourceView* m_texture8;   // Texture
    ID3D11ShaderResourceView* m_texture9;   // Texture
    std::unique_ptr<BlendState> m_blendState;
};
#endif


#if 0
 //旧版。UVで死ぬ
// 数字を表示する
// @ Memo : 生成位置から右に表示します
class NumberShow : public Component {
public:
    // コンストラクタ
    // @ Arg1 : ゲームオブジェクト
    NumberShow(GameObject* gameObject);

    // 数字セッター
    void SetNumber(const unsigned int in) { m_number = in; }

    // 表示間隔セッター
    void SetShowDistance(const float in) { m_showDistance = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    unsigned int m_number;                  // 表示する数字
    float        m_showDistance;            // 表示間隔
    ID3D11ShaderResourceView* m_texture;    // Texture
};
#endif


#endif // !____NUMBER_H____
