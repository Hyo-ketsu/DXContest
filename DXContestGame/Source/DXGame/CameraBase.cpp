#include <DXGame/CameraBase.h>
#include <DXGame/GameObject.h>
#include <DXGame/CameraSystem.h>


// �R���X�g���N�^
CameraBase::CameraBase(GameObject* gameObject, const bool isMainCamera)
    : Component(gameObject)
    , m_isMainCamera(isMainCamera)
    , m_look(0.0f,0.1f,0.0f)
    , m_up(0.0f,0.1f,0.0f)
    , m_fovy(60.0f * 3.14f / 180)
    , m_aspect(16.0f / 9.0f)
    , m_near(0.1f)
    , m_far(1000.0f) {
    //----- �J�����̓o�^
    CameraSystem::Get()->AddCamera(this);
}
// �f�X�g���N�^
CameraBase:: ~CameraBase(void) {
    //----- �J�����̓o�^����
    CameraSystem::Get()->DeleteCamera(this);
}


// �r���[�s��̎擾
const DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix(void) const {
    //------ �ϐ��錾
    DirectX::XMMATRIX view;     // �r���[�s��
    auto pos = m_gameObject->GetTransform().pos;    // �Q�[���I�u�W�F�N�g�̍��W

    //----- �r���[�s��̎擾
    view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(pos.x   , pos.y   , pos.z   , 0.0f),
        DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f), 
        DirectX::XMVectorSet(m_up.x  , m_up.y  , m_up.z  , 0.0f));

    //----- �ԋp�p�ϐ��錾
    DirectX::XMFLOAT4X4 ret;    // �ԋp�p4x4�z��

    //----- �ԋp
    view = DirectX::XMMatrixTranspose(view);    // �]�u
    DirectX::XMStoreFloat4x4(&ret, view);       
    return ret; 
}
// �v���W�F�N�V�����s��̎擾
const DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix(void) const {
    //----- �ϐ��錾
    DirectX::XMMATRIX proj; // �v���W�F�N�V�����s��

    //----- �v���W�F�N�V�����s��̎擾
    proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);

    //----- �ԋp�p�ϐ��錾
    DirectX::XMFLOAT4X4 ret;

    proj = DirectX::XMMatrixTranspose(proj);    // �]�u
    DirectX::XMStoreFloat4x4(&ret, proj);
    return ret;
}
