#ifndef ____FILESTORAGE_H____
#define ____FILESTORAGE_H____

#include <mutex>
#include <DXGame/ClassName.h>
#include <DXGame/FilePath.h>
#include <DXGame/Singleton.h>
#include <DXGame/Model.h>


using UseModel = bool;  // そのモデルが使用できるか


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
    // @ Memo : 成る丈使用したら返却できるようラップされたクラス（ModelComponent）をお使いください
    // @ Ret  : 読み込んだファイルへのポインタ
    // @ Arg1 : 読み込むファイル
    // @ Arg2 : モデルのスケール（デフォルト：1.0f）
    // @ Arg3 : 座標系の反転を行うか（デフォルト：false）
    Model* const LoadModel(const std::string& fileName, const float scale = 1.0f, const bool flip = false);


    // 使用したモデルを返却する
    // @ Arg1 : 返却するモデル
    void ReturnModel(const Model* const model);


private:
    // コンストラクタ
    FileStorage(void);


    // friendクラス宣言
    friend class Singleton<FileStorage>;

    std::unordered_map<std::string, ID3D11ShaderResourceView *const> m_texture; // テクスチャーを保持しておく連想配列
    std::unordered_multimap<std::string, std::pair<UseModel, std::unique_ptr<Model>>> m_model;   // モデルを保持しておく連想配列
    std::recursive_mutex m_modelMutex;    // モデル用ミューテックス
};


#endif // !____FILESTORAGE_H____
