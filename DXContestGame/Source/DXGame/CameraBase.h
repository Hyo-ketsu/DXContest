#ifndef ____CAMERABASE_H____
#define ____CAMERABASE_H____

#include <DXGame/ClassName.h>
#include <DXGame/Component.h>


// �J�����R���|�[�l���g
class CameraBase : public Component {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    // @ Arg2 : ���C���J�����ɐݒ肷�邩�i�f�t�H���g�Ffalse�j
    CameraBase(GameObject* gameObject, const bool isMainCamera = false);
    // �f�X�g���N�^
    virtual ~CameraBase(void) override;


    // ���C���J�����Q�b�^�[
    const bool GetMainCamera(void) const { return m_isMainCamera; }
    // ���C���J�����Z�b�^�[
    void SetMainCamera(const bool in) { m_isMainCamera = in; }


    // �����_�Q�b�^�[
    DirectX::XMFLOAT3 GetLook(void) const { return m_look; }


    // �r���[�s��̎擾
    // @ Ret  : �r���[�s��
    const DirectX::XMFLOAT4X4 GetViewMatrix(void) const;
    // �v���W�F�N�V�����s��̎擾
    // @ Ret  : �v���W�F�N�V�����s��
    const DirectX::XMFLOAT4X4 GetProjectionMatrix(void) const;

protected:
    bool              m_isMainCamera;   // ���C���J�����Ƃ��Đݒ肳��Ă��邩
    DirectX::XMFLOAT3 m_look;   // �����_
    DirectX::XMFLOAT3 m_up;     // 
    float             m_fovy;   // ����p
    float             m_aspect; // ��ʔ䗦
    float             m_near;   // �ŒZ�`�拗��
    float             m_far;    // �Œ��`�拗��
};


#endif // !____CAMERABASE_H____
