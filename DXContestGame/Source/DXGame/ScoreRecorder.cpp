#include <DXGame/ScoreRecorder.h>
#include <DXGame/ScoreIO.h>
#include <DXGame/FilePath.h>


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
        //----- �ێ����Ă���n�C�X�R�A�X�V
        m_highScore = m_score;
    }
}


// �n�C�X�R�A�������L���O�ɓo�^����
void ScoreGlobalRecorder::AddHighScoreRanking(void) const {
    //----- �����L���O�̍X�V
    ScoreRanking::Get()->AddScore(m_highScore);
}
