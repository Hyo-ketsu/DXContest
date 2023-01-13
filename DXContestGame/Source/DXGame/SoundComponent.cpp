#include <DXGame/SoundComponent.h>
#include <DXGame/Utility.h>
#include <DXGame/FilePath.h>


// �R���X�g���N�^
SoundVolumeSetter::SoundVolumeSetter(void) {
    SetBGMVolume(SOUND_VOLUME);
    SetSEVolume(SOUND_VOLUME);
}
// BGM���ʂ��Z�b�g����
void SoundVolumeSetter::SetBGMVolume(const float volume) {
    //----- ���ʃZ�b�g
    m_bgmVolume = volume;

    //----- ���ʍő�E�ŏ��l�ۂߍ���
    if (m_bgmVolume < 0.f) m_bgmVolume = 0.f;
    if (m_bgmVolume > 1.f) m_bgmVolume = 1.f;
}
// SE���ʂ��Z�b�g����
void SoundVolumeSetter::SetSEVolume(const float volume) {
    //----- ���ʃZ�b�g
    m_seVolume = volume;

    //----- ���ʍő�E�ŏ��l�ۂߍ���
    if (m_seVolume < 0.f) m_seVolume = 0.f;
    if (m_seVolume > 1.f) m_seVolume = 1.f;
}


std::unique_ptr<IXAudio2SourceVoice> SoundComponent::ms_buffer; // �T�E���h�o�b�t�@


// �R���X�g���N�^
SoundComponent::SoundComponent(GameObject* gameObject, std::string& file, const bool isBGM)
    : Component(gameObject)
    , m_source(std::unique_ptr<XAUDIO2_BUFFER>(CreateSound(Utility::MergeString(FilePath::SOUND_PATH,file).c_str(), isBGM))) {
}


// �Đ����J�n����
void SoundComponent::StartSound(void) {
    ms_buffer = std::unique_ptr<IXAudio2SourceVoice>(StartSoundOn(m_source.get()));
}
// �Đ����~����
void SoundComponent::StopSound(void) {
    ms_buffer->Stop();
}
