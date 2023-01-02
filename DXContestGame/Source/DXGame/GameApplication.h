#ifndef ____GAMEAPPLICATION_H____
#define ____GAMEAPPLICATION_H____

#include <DXGame/Singleton.h>


// �Q�[���̏I���Ȃǂ̃Q�[���S�̂̊Ǘ�������N���X
class GameApplication : public Singleton<GameApplication> {
public:
    // �Q�[���I���Q�b�^�[
    const bool GetGameEnd(void) const { return m_isGameEnd; }
    // �Q�[���I���Z�b�^�[
    void SetGameEnd(const bool in) { m_isGameEnd = in; }


private:
    // �R���X�g���N�^
    GameApplication(void);


    // �t�����h�錾
    friend class Singleton<GameApplication>;

    bool m_isGameEnd;   // �Q�[�����I��������
};


#endif // !____GAMEAPPLICATION_H____
