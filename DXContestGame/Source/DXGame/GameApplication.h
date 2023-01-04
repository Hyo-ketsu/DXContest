#ifndef ____GAMEAPPLICATION_H____
#define ____GAMEAPPLICATION_H____

#include <DXGame/Singleton.h>


// �Q�[���̏I���Ȃǂ̃Q�[���S�̂̊Ǘ�������N���X
class GameApplication : public Singleton<GameApplication> {
public:
    // �f�X�g���N�^
    ~GameApplication(void) override;


    // �Q�[���I���Q�b�^�[
    const bool GetGameEnd(void) const { return m_isGameEnd; }
    // �Q�[���I���Z�b�^�[
    void SetGameEnd(const bool in) { m_isGameEnd = in; }


    // �E�B���h�E���T�C�Y�Q�b�^�[
    const unsigned int GetWindowSizeX(void) const { return m_windowSizeX; }
    // �E�B���h�E���T�C�Y�Z�b�^�[
    void SetWindowSizeX(const unsigned int in) { m_windowSizeX = in; }
    // �E�B���h�E�c�T�C�Y�Q�b�^�[
    const unsigned int GetWindowSizeY(void) const { return m_windowSizeY; }
    // �E�B���h�E�c�T�C�Y�Z�b�^�[
    void SetWindowSizeY(const unsigned int in) { m_windowSizeY = in; }


private:
    // �R���X�g���N�^
    GameApplication(void);


    // �t�����h�錾
    friend class Singleton<GameApplication>;

    bool m_isGameEnd;   // �Q�[�����I��������
    unsigned int m_windowSizeX;   // �E�B���h�E�̉��T�C�Y
    unsigned int m_windowSizeY;   // �E�B���h�E�̏c�T�C�Y
};


#endif // !____GAMEAPPLICATION_H____
