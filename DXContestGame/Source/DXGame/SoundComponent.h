#ifndef ____SOUNDCOMPONENT_H____
#define ____SOUNDCOMPONENT_H____

#include <DXGame/Sound.h>
#include <DXGame/Component.h>
#include <DXGame/Singleton.h>


const float SOUND_VOLUME = 0.5f;    // ��������


// ���ʂ��Ǘ�����N���X
class SoundVolumeSetter : public Singleton<SoundVolumeSetter>{
public:
    // �f�X�g���N�^
    ~SoundVolumeSetter(void) {}


    // BGM���ʃQ�b�^�[
    const float GetBGMVolume(void) const { return m_bgmVolume; }
    // SE���ʃQ�b�^�[
    const float GetSEVolume(void) const { return m_seVolume; }


    // BGM���ʂ��Z�b�g����
    // @ Arg1 : �Z�b�g���鉹��(0 ~ 1)
    void SetBGMVolume(const float volume);
    // SE���ʂ��Z�b�g����
    // @ Arg1 : �Z�b�g���鉹��(0 ~ 1)
    void SetSEVolume(const float volume);


private:
    // �R���X�g���N�^
    SoundVolumeSetter(void);


    friend class Singleton<SoundVolumeSetter>;

    float m_bgmVolume;  // BGM����
    float m_seVolume;   // SE����
};


class SoundComponent : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    // @ Arg2 : �Đ��T�E���h��
    // @ Arg3 : BGM�ł����True
    // @ Arg4 : ���̃R���|�[�l���g���A�^�b�`����Ă���Q�[���I�u�W�F�N�g���������ꂽ�ۂɍĐ����~�߂邩�i�f�t�H���g�Ftrue�j
    SoundComponent(GameObject* gameObject, const std::string& file, const bool isBGM, const bool isDeadStop = true);
    // �f�X�g���N�^
    ~SoundComponent(void) override;


    void Start(void) override {}
    void Update(void) override final;


    // �Đ����J�n����
    void StartSound(void);
    // �Đ����~����
    // @ Memo : ���ӁFComponent�P�ʂł͂Ȃ��S���̃T�E���h���~�߂܂�
    void StopSound(void);

private:
    static IXAudio2SourceVoice* ms_buffer; // �T�E���h�o�b�t�@
    XAUDIO2_BUFFER*             m_source;  // �T�E���h�\�[�X
    const bool mc_isBGM;        // BGM���i�����[�v�Đ�������j
    const bool mc_isDeadStop;   // �폜���ɍĐ����~�߂邩
};


#endif // !____SOUNDCOMPONENT_H____
