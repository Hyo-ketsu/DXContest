#include "CameraBase.h"

// コンストラクタ
CameraBase::CameraBase(void) 
    : m_pos(0.0f,0.0f,0.0f)
    , m_look(0.0f,0.1f,0.0f)
    , m_up(0.0f,0.1f,0.0f)
    , m_fovy(60.0f * 3.14f / 180)
    , m_aspect(16.0f / 9.0f)
    , m_near(0.1f)
    , m_far(1000.0f) {
}

// ビュー行列の取得
DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix(void) {
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMMATRIX view;
    view = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f), 
        DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f), DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f));
    view = DirectX::XMMatrixTranspose(view);
    DirectX::XMStoreFloat4x4(&mat, view);
    return mat;
}

// プロジェクション行列の取得
DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix(void) {
    DirectX::XMFLOAT4X4 mat;
    DirectX::XMMATRIX proj;
    proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);
    proj = DirectX::XMMatrixTranspose(proj);
    DirectX::XMStoreFloat4x4(&mat, proj);
    return mat;
}
