#include <DXGame/FileStorage.h>
#include <DXGame/FilePath.h>
#include <DXGame/DirectXTex/Texture.h>


// デストラクタ
FileStorage::~FileStorage(void) {
}


// テクスチャーを読み込む
ID3D11ShaderResourceView* FileStorage::LoadTexture(const std::string& fileName) {
    //----- 変数宣言
    ID3D11ShaderResourceView* ret = nullptr;

    //----- 既に存在するか
    if (m_texture.find(fileName) == m_texture.end()) {
        //----- 存在する
        ret = m_texture.find(fileName)->second;
    }
    else {
        //----- 存在しないため読み込み
        LoadTextureFromFile(std::string(FilePath::TEXTURE_PATH + fileName).c_str(), &ret);
        m_texture.emplace(fileName, ret);
    }

    //----- 返却
    return ret;
}


// モデルを読み込む
Model FileStorage::LoadModel(const std::string& fileName, const float scale, const bool flip) {
    //----- 変数宣言
    Model ret;

    //----- 既に存在するか
    if (m_model.find(fileName) == m_model.end()) {
        //----- 存在する
        ret = m_model.find(fileName)->second;
    }
    else {
        //----- 存在しないため読み込み
        ret.Load(std::string(FilePath::MODEL_PATH + fileName).c_str(), scale, flip);
        m_model.emplace(fileName, ret);
    }

    //----- 返却
    return ret;
}


// コンストラクタ
FileStorage::FileStorage(void) {
}
