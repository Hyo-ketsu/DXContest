#ifndef ____MODELCOMPONENT_H____
#define ____MODELCOMPONENT_H____

#include <DXGame/Model.h>
#include <DXGame/Component.h>
#include <DXGame/ConstantBuffer.h>


// ModelClassをラップ、コンポーネント的に扱えるようにしたコンポーネント
class ModelComponent : public Component {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    // @ Arg2 : 読み込むファイル名
    // @ Arg3 : モデルのスケール（デフォルト：1.0f）
    // @ Arg4 : 座標系の反転を行うか（デフォルト：false）
    ModelComponent(GameObject* gameObject, const std::string& fileName, const float scale = 1.0f, const bool flip = false);
    // デストラクタ
    ~ModelComponent(void) override;


    // 初期化処理
    void Start(void) override;
    // 描画処理
    void Draw(void) override;


private:
    Model*                          m_model;    // モデル
    std::unique_ptr<ConstantBuffer> m_wvp;      // コンスタントバッファー
    std::unique_ptr<VertexShader>   m_vs;       // 頂点シェーダー
};


#endif // !____MODELCOMPONENT_H____
