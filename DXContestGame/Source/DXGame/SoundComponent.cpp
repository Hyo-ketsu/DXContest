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


IXAudio2SourceVoice* SoundComponent::ms_buffer = nullptr; // �T�E���h�o�b�t�@


// �R���X�g���N�^
SoundComponent::SoundComponent(GameObject* gameObject, const std::string& file, const bool isBGM, const bool isDeadStop)
    : Component(gameObject)
    , m_source(CreateSound(Utility::MergeString(FilePath::SOUND_PATH, file).c_str(), isBGM))
    , mc_isBGM(isBGM)
    , mc_isDeadStop(isDeadStop) {
}
// �f�X�g���N�^
SoundComponent::~SoundComponent(void) {
    if (mc_isDeadStop) {
        StopSound();
    }
}


void SoundComponent::Update(void) {
    //----- ����̃{�����[�����Z�b�g����
    ms_buffer->SetVolume(mc_isBGM ? SoundVolumeSetter::Get()->GetBGMVolume() : SoundVolumeSetter::Get()->GetSEVolume());
}


// �Đ����J�n����
void SoundComponent::StartSound(void) {
    //----- �Đ����J�n�A�i�[����
    ms_buffer = StartSoundOn(m_source);

    //----- ����̃{�����[�����Z�b�g����
    ms_buffer->SetVolume(mc_isBGM ? SoundVolumeSetter::Get()->GetBGMVolume() : SoundVolumeSetter::Get()->GetSEVolume());
}
// �Đ����~����
void SoundComponent::StopSound(void) {
    if (ms_buffer != nullptr) {
        ms_buffer->Stop();
    }
}
