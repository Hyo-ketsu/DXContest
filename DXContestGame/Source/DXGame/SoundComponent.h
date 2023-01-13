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


    // BGM音量ゲッター
    const float GetBGMVolume(void) const { return m_bgmVolume; }
    // SE音量ゲッター
    const float GetSEVolume(void) const { return m_seVolume; }


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
    // @ Arg4 : このコンポーネントがアタッチされているゲームオブジェクトが消去された際に再生を止めるか（デフォルト：true）
    SoundComponent(GameObject* gameObject, const std::string& file, const bool isBGM, const bool isDeadStop = true);
    // デストラクタ
    ~SoundComponent(void) override;


    void Start(void) override {}
    void Update(void) override final;


    // 再生を開始する
    void StartSound(void);
    // 再生を停止する
    // @ Memo : 注意：Component単位ではなく全部のサウンドを止めます
    void StopSound(void);

private:
    static IXAudio2SourceVoice* ms_buffer; // サウンドバッファ
    XAUDIO2_BUFFER*             m_source;  // サウンドソース
    const bool mc_isBGM;        // BGMか（＝ループ再生をする）
    const bool mc_isDeadStop;   // 削除時に再生を止めるか
};


#endif // !____SOUNDCOMPONENT_H____
