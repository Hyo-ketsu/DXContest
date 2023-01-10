#include <DXGame/FileStorage.h>
#include <DXGame/FilePath.h>
#include <DXGame/DirectXTex/Texture.h>
#include <DXGame/Utility.h>
#include <DXGame/SceneLoader.h>


// デストラクタ
FileStorage::~FileStorage(void) {
    SceneLoader::Get()->DeleteInstance();
}


// テクスチャーを読み込む
ID3D11ShaderResourceView* FileStorage::LoadTexture(const std::string& fileName) {
    //----- 変数宣言
    ID3D11ShaderResourceView* ret = nullptr;

    //----- 既に存在するか
    if (m_texture.find(fileName) != m_texture.end()) {
        //----- 存在する
        ret = m_texture.find(fileName)->second;
    }
    else {
        //----- 存在しないため読み込み
        LoadTextureFromFile(Utility::MergeString(FilePath::TEXTURE_PATH, fileName).c_str(), &ret);
        m_texture.emplace(fileName, ret);
    }

    //----- 返却
    return ret;
}


// モデルを読み込む
Model* const FileStorage::LoadModel(const std::string& fileName, const float scale, const bool flip) {
    //----- ロック
    m_modelMutex.lock();
    
    //----- 変数宣言
    auto data = m_model.find(fileName);
    
    //----- モデルがあるか（あればモデルを取得して返却する）
    for (; data != m_model.end(); data++) {
        //----- 使用済みか
        if (data->second.first == false) {
            //----- 使われていない。このモデルを使用
            data->second.first = true;          // 使用済みとする
            return data->second.second.get();
        }
    }

    //----- モデルがない。読み込んで追加
    Model* model = new Model();
    // 先行して"使用済み"として追加（読み込み後に開放する）
    auto it = m_model.emplace(std::pair<std::string, std::pair<UseModel, std::unique_ptr<Model>>>(
        fileName, std::pair<UseModel, std::unique_ptr<Model>>(true, std::unique_ptr<Model>(model))
        )
    );

    //----- ロック解除
    m_modelMutex.unlock();

    //----- モデル読み込み
    model->Load(std::string(FilePath::MODEL_PATH + fileName), scale, flip);

    //----- ロック
    std::scoped_lock<std::recursive_mutex> lock(m_modelMutex);

    // 読み込み完了。"未使用"として開放
    it->second.first = false;

    //----- 返却
    return model;
}


// 使用したモデルを返却する
void FileStorage::ReturnModel(const Model* const model) {
    //----- 同ポインタのモデルを検索
    for (auto& it : m_model) {
        if (it.second.second.get() == model) {
            //----- 同ポインタのモデル。使用済みを開放する
            it.second.first = false;
        }
    }
}


// コンストラクタ
FileStorage::FileStorage(void) {
}
