#include <DXGame/SoundComponent.h>
#include <DXGame/Utility.h>
#include <DXGame/FilePath.h>


// コンストラクタ
SoundVolumeSetter::SoundVolumeSetter(void) {
    SetBGMVolume(SOUND_VOLUME);
    SetSEVolume(SOUND_VOLUME);
}
// BGM音量をセットする
void SoundVolumeSetter::SetBGMVolume(const float volume) {
    //----- 音量セット
    m_bgmVolume = volume;

    //----- 音量最大・最小値丸め込み
    if (m_bgmVolume < 0.f) m_bgmVolume = 0.f;
    if (m_bgmVolume > 1.f) m_bgmVolume = 1.f;
}
// SE音量をセットする
void SoundVolumeSetter::SetSEVolume(const float volume) {
    //----- 音量セット
    m_seVolume = volume;

    //----- 音量最大・最小値丸め込み
    if (m_seVolume < 0.f) m_seVolume = 0.f;
    if (m_seVolume > 1.f) m_seVolume = 1.f;
}


std::unique_ptr<IXAudio2SourceVoice> SoundComponent::ms_buffer; // サウンドバッファ


// コンストラクタ
SoundComponent::SoundComponent(GameObject* gameObject, std::string& file, const bool isBGM)
    : Component(gameObject)
    , m_source(std::unique_ptr<XAUDIO2_BUFFER>(CreateSound(Utility::MergeString(FilePath::SOUND_PATH,file).c_str(), isBGM))) {
}


// 再生を開始する
void SoundComponent::StartSound(void) {
    ms_buffer = std::unique_ptr<IXAudio2SourceVoice>(StartSoundOn(m_source.get()));
}
// 再生を停止する
void SoundComponent::StopSound(void) {
    ms_buffer->Stop();
}
