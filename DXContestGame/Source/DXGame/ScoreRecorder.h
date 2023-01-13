#ifndef ____SCORERECORDER_H____
#define ____SCORERECORDER_H____

#include <DXGame/GameObject.h>
#include <DXGame/Singleton.h>


// �X�R�A��ێ�����
class ScoreGlobalRecorder : public Singleton<ScoreGlobalRecorder> {
public:
    // �f�X�g���N�^
    ~ScoreGlobalRecorder(void) override;


    // ���X�R�A�Q�b�^�[
    const unsigned int GetScore(void) const { return m_score; }
    // ���X�R�A�Z�b�^�[
    void SetScore(const unsigned int in); 


    // �n�C�X�R�A�Q�b�^�[
    const unsigned int GetHighScore(void) const { return m_highScore; }

private:
    // �R���X�g���N�^
    ScoreGlobalRecorder(void);


    friend class Singleton<ScoreGlobalRecorder>;

    unsigned int m_score;       // �ێ��X�R�A
    unsigned int m_highScore;   // �ێ��n�C�X�R�A
};


#endif // !____SCORERECORDER_H____
