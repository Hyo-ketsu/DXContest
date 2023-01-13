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


IXAudio2SourceVoice* SoundComponent::ms_buffer = nullptr; // サウンドバッファ


// コンストラクタ
SoundComponent::SoundComponent(GameObject* gameObject, const std::string& file, const bool isBGM, const bool isDeadStop)
    : Component(gameObject)
    , m_source(CreateSound(Utility::MergeString(FilePath::SOUND_PATH, file).c_str(), isBGM))
    , mc_isBGM(isBGM)
    , mc_isDeadStop(isDeadStop) {
}
// デストラクタ
SoundComponent::~SoundComponent(void) {
    if (mc_isDeadStop) {
        StopSound();
    }
}


void SoundComponent::Update(void) {
    //----- 現状のボリュームをセットする
    ms_buffer->SetVolume(mc_isBGM ? SoundVolumeSetter::Get()->GetBGMVolume() : SoundVolumeSetter::Get()->GetSEVolume());
}


// 再生を開始する
void SoundComponent::StartSound(void) {
    //----- 再生を開始、格納する
    ms_buffer = StartSoundOn(m_source);

    //----- 現状のボリュームをセットする
    ms_buffer->SetVolume(mc_isBGM ? SoundVolumeSetter::Get()->GetBGMVolume() : SoundVolumeSetter::Get()->GetSEVolume());
}
// 再生を停止する
void SoundComponent::StopSound(void) {
    if (ms_buffer != nullptr) {
        ms_buffer->Stop();
    }
}
