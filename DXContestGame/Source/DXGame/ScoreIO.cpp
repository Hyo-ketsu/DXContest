#include <DXGame/ScoreIO.h>
#include <fstream>


// �X�R�A�t�@�C����ǂݍ���
const ScoreArray ScoreIO::ReadScore(void) {
    //----- �ϐ��錾
    std::vector<unsigned int> score;  // �ԋp�p�X�R�A���I�z��
    ScoreArray ret; // �ԋp�p�X�R�A�z��
    std::string line;   // �ǂݍ��񂾍s
    std::string token;  // �ǂݍ��񂾕�����

    //----- �󂩔���
    FilePathEmpty();

    //----- �ǂݍ��݃X�g���[���錾
    std::ifstream file(m_filePath);
    if (!(file)) {
        ret.fill(0);
        return ret;
    }

    //----- ���l�ǂݍ���
    while (std::getline(file, line)) {
        //----- �ǂݍ��񂾍s�̉��
        for (auto lineChar : line) {
            //----- ��؂蕶���i,�j�Ⴕ���͉��s�ɓ��B������
            if (lineChar == ',' || lineChar == '\n') {
                //----- ���B�B�ǂݍ��񂾃g�[�N����ϊ�
                if (token.empty() == false) {
                    //----- �g�[�N������łȂ��B���l�ϊ�
                    score.push_back(std::stoi(token));

                    //----- �g�[�N��������
                    token.clear();
                }
            }
            else {
                //----- ���B���Ă��Ȃ��B1�������g�[�N���ɒǉ�
                token += lineChar;
            }
        }
    }

    //----- ���I�z�񂩂�ԋp�z��ֈڂ�
    ret.fill(0);    // ���̏��ʂɐ��l���Ȃ���� 0 �ɂ��邽��
    for (int i = 0;; i++) {
        //----- ���I�z��A�ԋp�z��ǂ�����͈͓����i�K�[�h�߁j
        if (score.size() >= i) break;
        if (ret.size()   >= i) break;

        //----- �l�̎󂯓n��
        ret[i] = score[i];
    }

    //----- �ԋp
    return std::move(ret);
}
// �X�R�A�t�@�C������������
void ScoreIO::WriteScore(const ScoreArray& scoreData) {
    //----- �󂩔���
    FilePathEmpty();

    // �t�@�C���I�[�v��
    std::ofstream file(m_filePath);

    //----- ��������
    for (auto it : scoreData) {
        //----- �X�R�A�o��
        file << it << ',';

        //----- ���s
        file << std::endl;
    }
}


// �ǂݍ��݃t�@�C���p�X���󂩔���A��O��f��
void ScoreIO::FilePathEmpty(void) const {
    //----- ����
    if (m_filePath.empty()) {
        //----- �����񂪋�B��O��f��
        throw std::exception("Error! ScoreIO file path empty");
    }
}
