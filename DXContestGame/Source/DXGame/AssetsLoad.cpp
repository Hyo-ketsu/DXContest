#include <DXGame/AssetsLoad.h>
#include <thread>
#include <DXGame/FileStorage.h>
#include <DXGame/GameDefine.h>


const int LOAD_ASSETS_SPRITE_COUNT = 32;    // 読み込み時の最大分割数


// どのファイル、個数読み込むかの情報を格納する構造体
struct LoadAssetsData {
    // コンストラクタ
    // @ Arg1 : 読み込みファイル名
    // @ Arg2 : 読み込み個数
    // @ Arg3 : 読み込み時のモデルの大きさ（デフォルト：1）
    // @ Arg4 : 読み込み時反転させるか（デフォルト：false）
    LoadAssetsData(const std::string& file, const unsigned int count, const float scale = 1.f, const bool flip = false) 
        : name(file)
        , count(count) 
        , scale(scale)
        , flip(flip) {
    }

    std::string name;  // 読み込みファイル名
    int         count; // 読み込み個数
    float       scale; // 読み込み時のモデルの大きさ
    bool        flip;  // 読み込み時反転させるか
};


using LoadAssetsList = std::vector<LoadAssetsData>;


// 指定ファイルを読み込む
// @ Arg1 : 読み込みファイル情報
void LoadFile(const LoadAssetsData& data) {
    //----- スレッド名変更
    SetThreadDescription(GetCurrentThread(), L"AssetsLoadThread");

    //----- COMオブジェクトの初期化
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    //----- 読み込み
    for (int i = 0; i < data.count; i++) {
        auto release = FileStorage::Get()->LoadModel(data.name, data.scale, data.flip);
        FileStorage::Get()->ReturnModel(release);
    }
}


// リストで指定したものを全て読み込む
void AllLoadFile(LoadAssetsList* list) {
    //----- 変数宣言
    std::vector<std::thread> threadList;    // 読み込み用スレッドの動的配列

    //----- 読み込みループ
    for (auto& it : *list) {
        //----- 読み込み
        while (it.count > 0) {  // 読み込み数がなくなる（＝全て読み込みが開始される）まで読み込む
            //----- 読み込み数の設定
            unsigned int loadFileCount = LOAD_ASSETS_SPRITE_COUNT;
            loadFileCount = ((it.count -= loadFileCount) < 0 ? LOAD_ASSETS_SPRITE_COUNT + it.count : LOAD_ASSETS_SPRITE_COUNT);// 読み込みすぎ（it.countが0以下）の場合はその分補正する

            //----- 読み込みの開始
            LoadAssetsData data(it.name,loadFileCount,it.scale,it.flip);
            threadList.push_back(std::thread(LoadFile, data));  // 読み込み開始
        }
    }

    //----- 全てのスレッド読み込みが終了するまで待機
    for (auto& it : threadList) {
        if (it.joinable()) {
            it.join();
        }
    }
}


// モデルなどを先行して読み込む
void FirstLoad(void) {
    //----- 変数宣言
    LoadAssetsList list;

    //----- 読み込みモデルの追加
    list.push_back(LoadAssetsData(LOAD_BLOCK_FILENAME    , 1, LOAD_BLOCK_SCALE));
    list.push_back(LoadAssetsData(LOAD_OBSTACLES_FILENAME, 1, LOAD_OBSTACLES_SCALE));
    list.push_back(LoadAssetsData(LOAD_PLAYER_FILENAME   , 1, LOAD_PLAYER_SCALE));

    //----- 読み込み
    AllLoadFile(&list);
}
