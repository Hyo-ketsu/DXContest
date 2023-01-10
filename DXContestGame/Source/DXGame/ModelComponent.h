#ifndef ____MODELCOMPONENT_H____
#define ____MODELCOMPONENT_H____

#include <DXGame/Model.h>
#include <DXGame/Component.h>
#include <DXGame/ConstantBuffer.h>


// ModelClass�����b�v�A�R���|�[�l���g�I�Ɉ�����悤�ɂ����R���|�[�l���g
class ModelComponent : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    // @ Arg2 : �ǂݍ��ރt�@�C����
    // @ Arg3 : ���f���̃X�P�[���i�f�t�H���g�F1.0f�j
    // @ Arg4 : ���W�n�̔��]���s�����i�f�t�H���g�Ffalse�j
    ModelComponent(GameObject* gameObject, const std::string& fileName, const float scale = 1.0f, const bool flip = false);
    // �f�X�g���N�^
    ~ModelComponent(void) override;


    // ����������
    void Start(void) override;
    // �`�揈��
    void Draw(void) override;


private:
    Model*                          m_model;    // ���f��
    std::unique_ptr<ConstantBuffer> m_wvp;      // �R���X�^���g�o�b�t�@�[
    std::unique_ptr<VertexShader>   m_vs;       // ���_�V�F�[�_�[
};


#endif // !____MODELCOMPONENT_H____
