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
    SoundComponent(GameObject* gameObject, std::string& file, const bool isBGM);


    void Start(void) override {}
    void Update(void) override {}


    // �Đ����J�n����
    void StartSound(void);
    // �Đ����~����
    // @ Memo : ���ӁFComponent�P�ʂł͂Ȃ��S���̃T�E���h���~�߂܂�
    void StopSound(void);

private:
    static std::unique_ptr<IXAudio2SourceVoice> ms_buffer; // �T�E���h�o�b�t�@
    std::unique_ptr<XAUDIO2_BUFFER>             m_source;  // �T�E���h�\�[�X
};


#endif // !____SOUNDCOMPONENT_H____
