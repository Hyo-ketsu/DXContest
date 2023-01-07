#ifndef ____FILESTORAGE_H____
#define ____FILESTORAGE_H____

#include <DXGame/ClassName.h>
#include <DXGame/FilePath.h>
#include <DXGame/Singleton.h>
#include <DXGame/Model.h>


// �ǂݍ��񂾃t�@�C����ێ����Ă����N���X
// @ Memo : �ǂݍ��ލۂ͓ǂݍ��ރt�@�C���ɂ���Ď����Ńp�X���擾���܂�
class FileStorage : public Singleton<FileStorage> {
public:
    // �f�X�g���N�^
    ~FileStorage(void) override;


    // �e�N�X�`���[��ǂݍ���
    // @ Ret  : �ǂݍ��񂾃t�@�C���ւ̃|�C���^
    // @ Arg1 : �ǂݍ��ރt�@�C��
    ID3D11ShaderResourceView* LoadTexture(const std::string& fileName);


    // ���f����ǂݍ���
    // @ Ret  : �ǂݍ��񂾃t�@�C���ւ̃|�C���^
    // @ Arg1 : �ǂݍ��ރt�@�C��
    // @ Arg2 : ���f���̃X�P�[���i�f�t�H���g�F1.0f�j
    // @ Arg3 : ���W�n�̔��]���s�����i�f�t�H���g�Ffalse�j
    Model* LoadModel(const std::string& fileName, const float scale = 1.0f, const bool flip = false);


private:
    // �R���X�g���N�^
    FileStorage(void);


    // friend�N���X�錾
    friend class Singleton<FileStorage>;

    std::unordered_map<std::string, ID3D11ShaderResourceView *const> m_texture; // �e�N�X�`���[��ێ����Ă����A�z�z��
    //std::unordered_map<std::string, std::unique_ptr<const Model>>    m_model;   // ���f����ێ����Ă����A�z�z��
};


#endif // !____FILESTORAGE_H____
