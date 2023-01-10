#ifndef ____NUMBER_H____
#define ____NUMBER_H____

#include <DXGame/Sprite.h>
#include <DXGame/GameObject.h>
#include <DXGame/BlendState.h>
#include <DXGame/BlendState.h>


#if 1
// ������\������
// @ Memo : �����ʒu����E�ɕ\�����܂�
class NumberShow : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �Q�[���I�u�W�F�N�g
    NumberShow(GameObject* gameObject);

    // �����Z�b�^�[
    void SetNumber(const unsigned int in) { m_number = in; }

    // �\���Ԋu�Z�b�^�[
    void SetShowDistance(const float in) { m_showDistance = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    unsigned int m_number;                  // �\�����鐔��
    float        m_showDistance;            // �\���Ԋu
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
 //���ŁBUV�Ŏ���
// ������\������
// @ Memo : �����ʒu����E�ɕ\�����܂�
class NumberShow : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �Q�[���I�u�W�F�N�g
    NumberShow(GameObject* gameObject);

    // �����Z�b�^�[
    void SetNumber(const unsigned int in) { m_number = in; }

    // �\���Ԋu�Z�b�^�[
    void SetShowDistance(const float in) { m_showDistance = in; }


    void Start(void) override;
    void Draw(void) override;

private:
    unsigned int m_number;                  // �\�����鐔��
    float        m_showDistance;            // �\���Ԋu
    ID3D11ShaderResourceView* m_texture;    // Texture
};
#endif


#endif // !____NUMBER_H____
