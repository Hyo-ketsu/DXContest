#ifndef ____SCORERANKING_H____
#define ____SCORERANKING_H____

#include <DXGame/Singleton.h>


// �O���錾
class ScoreIO;


const unsigned int SCORE_RANKING = 3;   // �����L���O�ɋL�^���鏇�ʐ�
const std::string  SCORE_RANKING_FILE_NAME = "ScoreRanking.csv";


using ScoreArray = std::array<unsigned int, SCORE_RANKING>; // �X�R�A��ێ�����z��^


// �n�C�X�R�A�����L���O�̓_���̂ݕێ����Ă����N���X
class ScoreRanking : public Singleton<ScoreRanking> {
public:
    // �f�X�g���N�^
    ~ScoreRanking(void);


    // �n�C�X�R�A�����L���O�ɒǉ�����
    // @ Arg1 : �o�^����X�R�A
    void AddScore(const unsigned int score);
    // �n�C�X�R�A�����L���O���擾����
    // @ Memo : �͈͊O�i�L�^Ranking�O�j���w�肵���ۂ͂��̂܂ܗ�O��f���܂�
    // @ Ret  : ���l�i���̏��ʂɃX�R�A�����݂��Ȃ��ꍇ��0��Ԃ��܂��j
    // @ Arg1 : �擾����������
    unsigned int GetScore(const unsigned int rank) const;

private:
    // �R���X�g���N�^
    ScoreRanking(void);


    friend class Singleton<ScoreRanking>;


    ScoreArray m_score;  // �e���ʂ̃X�R�A���W�߂��ۑ������N���X�i���_�~���j
    std::unique_ptr<ScoreIO> m_scoreIO; // �X�R�A���o�͗p�N���X
};


#endif // !____SCORERANKING_H____
