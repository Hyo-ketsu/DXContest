#ifndef ____SOUNDCOMPONENT_H____
#define ____SOUNDCOMPONENT_H____

#include <DXGame/Sound.h>
#include <DXGame/Component.h>
#include <DXGame/Singleton.h>


const float SOUND_VOLUME = 0.5f;    // 初期音量


// 音量を管理するクラス
class SoundVolumeSetter : public Singleton<SoundVolumeSetter>{
public:
    // デストラクタ
    ~SoundVolumeSetter(void) {}


    // BGM音量をセットする
    // @ Arg1 : セットする音量(0 ~ 1)
    void SetBGMVolume(const float volume);
    // SE音量をセットする
    // @ Arg1 : セットする音量(0 ~ 1)
    void SetSEVolume(const float volume);


private:
    // コンストラクタ
    SoundVolumeSetter(void);


    friend class Singleton<SoundVolumeSetter>;

    float m_bgmVolume;  // BGM音量
    float m_seVolume;   // SE音量
};


class SoundComponent : public Component {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    // @ Arg2 : 再生サウンド名
    // @ Arg3 : BGMであればTrue
    SoundComponent(GameObject* gameObject, std::string& file, const bool isBGM);


    void Start(void) override {}
    void Update(void) override {}


    // 再生を開始する
    void StartSound(void);
    // 再生を停止する
    // @ Memo : 注意：Component単位ではなく全部のサウンドを止めます
    void StopSound(void);

private:
    static std::unique_ptr<IXAudio2SourceVoice> ms_buffer; // サウンドバッファ
    std::unique_ptr<XAUDIO2_BUFFER>             m_source;  // サウンドソース
};


#endif // !____SOUNDCOMPONENT_H____
