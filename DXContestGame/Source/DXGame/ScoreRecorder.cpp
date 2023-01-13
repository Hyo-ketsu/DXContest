#include <DXGame/ScoreRecorder.h>


// �R���X�g���N�^
ScoreGlobalRecorder::ScoreGlobalRecorder(void)
    : m_score(0) 
    , m_highScore(0) {
}


// �f�X�g���N�^
ScoreGlobalRecorder::~ScoreGlobalRecorder(void) {
}


// ���X�R�A�Z�b�^�[
void ScoreGlobalRecorder::SetScore(const unsigned int in) {
    //----- ���X�R�A�X�V
    m_score = in; 

    //----- �n�C�X�R�A�X�V
    if (m_highScore < m_score) {
        m_highScore = m_score;
    }
}
