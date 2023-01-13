#ifndef _____SPRITECOMPONENT_H____
#define _____SPRITECOMPONENT_H____

#include <DXGame/GameObject.h>


class SpriteShowComponent : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �Q�[���I�u�W�F�N�g
    // @ Arg2 : �X�v���C�g�t�@�C����
    SpriteShowComponent(GameObject* gameObject, const std::string& file);


    // �F�Q�b�^�[
    const DirectX::XMFLOAT4 GetColor(void) const { return m_color; }
    // �F�Z�b�^�[
    void SetColor(const DirectX::XMFLOAT4& in) { m_color = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    const std::string         m_fileName;   // �t�@�C���ǂݍ��݁A
    ID3D11ShaderResourceView* m_sprite;     // �\���X�v���C�g
    DirectX::XMFLOAT4         m_color;      // �F
};


#endif // !_____SPRITECOMPONENT_H____
