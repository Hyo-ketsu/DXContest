#ifndef ____MODELCOMPONENT_H____
#define ____MODELCOMPONENT_H____

#include <DXGame/Model.h>
#include <DXGame/Component.h>
#include <DXGame/ConstantBuffer.h>


// ModelClassをラップ、コンポーネント的に扱えるようにしたコンポーネント
class ModelComponent : public Component {
public:
    // コンストラクタ
    // @ Arg1 : 読み込むファイル名
    ModelComponent(const std::string& fileName);


    // 初期化処理
    void Start(void) override;
    // 描画処理
    void Draw(void) override;


private:
    std::unique_ptr<Model>          m_model;    // モデル
    std::unique_ptr<ConstantBuffer> m_wvp;      // コンスタントバッファー
};


#endif // !____MODELCOMPONENT_H____
