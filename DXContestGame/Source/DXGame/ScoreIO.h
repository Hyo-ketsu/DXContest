#ifndef ____SCOREIO_H____
#define ____SCOREIO_H____

#include <DXGame/Component.h>
#include <DXGame/ScoreRanking.h>


// �X�R�A���o�́E���͂��s���N���X
class ScoreIO {
public:
    // �ǂݍ��݃t�@�C���p�X�Q�b�^�[
    const std::string& GetFilePath(void) const { return m_filePath; }
    // �ǂݍ��݃t�@�C���p�X�Z�b�^�[
    void SetFilePath(const std::string& in) { m_filePath = in; }


    // �X�R�A�t�@�C����ǂݍ���
    // @ Memo : �ǂݍ��݃t�@�C�����w�肳��Ă��Ȃ��ꍇ��O�𓊂��܂�
    // @ Ret  : �ǂݍ��񂾃X�R�A�f�[�^�̔z��
    const ScoreArray ReadScore(void);
    // �X�R�A�t�@�C������������
    // @ Memo : �ǂݍ��݃t�@�C�����w�肳��Ă��Ȃ��ꍇ��O�𓊂��܂�
    // @ Arg1 : �������ރX�R�A�f�[�^�̔z��
    void WriteScore(const ScoreArray& scoreData);

private:
    // �ǂݍ��݃t�@�C���p�X���󂩔���A��O��f��
    // @ Memo : �ǂݍ��݃t�@�C���p�X����ł���Η�O��f���܂�
    void FilePathEmpty(void) const;


    std::string m_filePath; // �ǂݍ��݃t�@�C���p�X
};


// ScoreIO���R���|�[�l���g�Ń��b�v�����N���X
class ScoreIOComponent : public ScoreIO, public Component {
public:
    void Start(void)  override {}
    void Update(void) override {}    
};


#endif // !____SCORELOAD_H____
