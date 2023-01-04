#ifndef ____MODELCOMPONENT_H____
#define ____MODELCOMPONENT_H____

#include <DXGame/Model.h>
#include <DXGame/Component.h>
#include <DXGame/ConstantBuffer.h>


// ModelClass�����b�v�A�R���|�[�l���g�I�Ɉ�����悤�ɂ����R���|�[�l���g
class ModelComponent : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �ǂݍ��ރt�@�C����
    ModelComponent(const std::string& fileName);


    // ����������
    void Start(void) override;
    // �`�揈��
    void Draw(void) override;


private:
    std::unique_ptr<Model>          m_model;    // ���f��
    std::unique_ptr<ConstantBuffer> m_wvp;      // �R���X�^���g�o�b�t�@�[
};


#endif // !____MODELCOMPONENT_H____
