#ifndef ____FILESTORAGE_H____
#define ____FILESTORAGE_H____

#include <DXGame/ClassName.h>
#include <DXGame/FilePath.h>
#include <DXGame/Singleton.h>
#include <DXGame/Model.h>


// 読み込んだファイルを保持しておくクラス
// @ Memo : 読み込む際は読み込むファイルによって自動でパスを取得します
class FileStorage : public Singleton<FileStorage> {
public:
    // デストラクタ
    ~FileStorage(void) override;


    // テクスチャーを読み込む
    // @ Ret  : 読み込んだファイルへのポインタ
    // @ Arg1 : 読み込むファイル
    ID3D11ShaderResourceView* LoadTexture(const std::string& fileName);


    // モデルを読み込む
    // @ Ret  : 読み込んだファイルへのポインタ
    // @ Arg1 : 読み込むファイル
    // @ Arg2 : モデルのスケール（デフォルト：1.0f）
    // @ Arg3 : 座標系の反転を行うか（デフォルト：false）
    Model* LoadModel(const std::string& fileName, const float scale = 1.0f, const bool flip = false);


private:
    // コンストラクタ
    FileStorage(void);


    // friendクラス宣言
    friend class Singleton<FileStorage>;

    std::unordered_map<std::string, ID3D11ShaderResourceView *const> m_texture; // テクスチャーを保持しておく連想配列
    //std::unordered_map<std::string, std::unique_ptr<const Model>>    m_model;   // モデルを保持しておく連想配列
};


#endif // !____FILESTORAGE_H____
