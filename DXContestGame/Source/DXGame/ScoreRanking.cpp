#include <DXGame/ScoreRanking.h>
#include <DXGame/ScoreIO.h>
#include <DXGame/FilePath.h>


// �n�C�X�R�A�����L���O�ɒǉ�����
void ScoreRanking::AddScore(const unsigned int score) {
    //----- �ϐ��錾
    auto it = m_score.begin();

    //----- �ǉ����邩����
    for (; it != m_score.end(); it++) {
        //----- ���̏��ʂ̃X�R�A���ǉ��X�R�A�̂ق����傫����
        if (score > *it) {
            //----- �傫���B�������߂�
            break;
        }
    }

    //----- �ǉ����s�������肷��
    if (it == m_score.end()) return;    // �C�e���[�^���Ō�ɓ��B���Ă���B�I��

    //----- �ǉ����s���B�Ō�̗v�f�ɑ���i�~���Ƀ\�[�g����Ă���̂ōŌオ�ŏ��̒l�ɂȂ邽�߁j
    m_score.at(m_score.size() - 1) = score;

    //----- �\�[�g����
    std::sort(m_score.begin(), m_score.end(), std::greater<unsigned int>());
}
// �n�C�X�R�A�����L���O���擾����
unsigned int ScoreRanking::GetScore(const unsigned int rank) const {
    //----- �ԋp
    return m_score.at(rank);
}


// �R���X�g���N�^
ScoreRanking::ScoreRanking(void) {
    //----- �����o������
    m_score.fill(0);
    m_scoreIO = std::make_unique<std::remove_reference_t<decltype(*m_scoreIO.get())>>();
    m_scoreIO->SetFilePath(FilePath::SCOREDATA_PATH + SCORE_RANKING_FILE_NAME);

    //----- �X�R�A�ǂݍ���
    m_score = m_scoreIO->ReadScore();
}
// �f�X�g���N�^
ScoreRanking::~ScoreRanking(void) {
    //----- �X�R�A�ۑ�
    m_scoreIO->WriteScore(m_score);
}
