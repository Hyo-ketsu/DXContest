#ifndef ____SCOREIO_H____
#define ____SCOREIO_H____

#include <DXGame/Component.h>
#include <DXGame/ScoreRanking.h>


// スコアを出力・入力を行うクラス
class ScoreIO {
public:
    // 読み込みファイルパスゲッター
    const std::string& GetFilePath(void) const { return m_filePath; }
    // 読み込みファイルパスセッター
    void SetFilePath(const std::string& in) { m_filePath = in; }


    // スコアファイルを読み込み
    // @ Memo : 読み込みファイルが指定されていない場合例外を投げます
    // @ Ret  : 読み込んだスコアデータの配列
    const ScoreArray ReadScore(void);
    // スコアファイルを書き込み
    // @ Memo : 読み込みファイルが指定されていない場合例外を投げます
    // @ Arg1 : 書き込むスコアデータの配列
    void WriteScore(const ScoreArray& scoreData);

private:
    // 読み込みファイルパスが空か判定、例外を吐く
    // @ Memo : 読み込みファイルパスが空であれば例外を吐きます
    void FilePathEmpty(void) const;


    std::string m_filePath; // 読み込みファイルパス
};


// ScoreIOをコンポーネントでラップしたクラス
class ScoreIOComponent : public ScoreIO, public Component {
public:
    void Start(void)  override {}
    void Update(void) override {}    
};


#endif // !____SCORELOAD_H____
