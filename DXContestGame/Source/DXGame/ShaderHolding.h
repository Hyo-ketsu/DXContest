#ifndef ____SHADERHOLDING_H___
#define ____SHADERHOLDING_H___

#include <DXGame/Singleton.h>
#include <DXGame/Shader.h>


class ShaderHolding : public Singleton<ShaderHolding> {
public:
    // デストラクタ
    ~ShaderHolding(void) override;

private:
    // コンストラクタ
    ShaderHolding(void);


    // フレンド宣言
    friend class Singleton<ShaderHolding>;
};


#endif // !____SHADERHOLDING_H___
