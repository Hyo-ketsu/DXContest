#ifndef ____SHADERHOLDING_H___
#define ____SHADERHOLDING_H___

#include <DXGame/Singleton.h>
#include <DXGame/Shader.h>


class ShaderHolding : public Singleton<ShaderHolding> {
public:
    // �f�X�g���N�^
    ~ShaderHolding(void) override;

private:
    // �R���X�g���N�^
    ShaderHolding(void);


    // �t�����h�錾
    friend class Singleton<ShaderHolding>;
};


#endif // !____SHADERHOLDING_H___
