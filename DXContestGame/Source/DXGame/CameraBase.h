#ifndef ____CAMERABASE_H____
#define ____CAMERABASE_H____


// �J�����̊�b�ƂȂ�N���X
class CameraBase {
public:
    // �R���X�g���N�^
    CameraBase(void);

    // �f�X�g���N�^
    virtual ~CameraBase(void) {}
    virtual void Update(void) = 0;

    // �r���[�s��̎擾
    DirectX::XMFLOAT4X4 GetViewMatrix(void);

    // �v���W�F�N�V�����s��̎擾
    DirectX::XMFLOAT4X4 GetProjectionMatrix(void);
    
    // �ʒu�̎擾
    DirectX::XMFLOAT3 GetPos(void) { return m_pos; }

    // �����_�̎擾
    DirectX::XMFLOAT3 GetLook(void) { return m_look; }

protected:
    DirectX::XMFLOAT3 m_pos, m_look, m_up;  // �r���[�s��̐ݒ�ɕK�v�ȕϐ�
    float m_fovy, m_aspect, m_near, m_far;  // �v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
};


#endif // !____CAMERABASE_H____
