#include <DXGame/CameraBase.h>
#include <DXGame/GameObject.h>
#include <DXGame/CameraSystem.h>


// コンストラクタ
CameraBase::CameraBase(GameObject* gameObject, const bool isMainCamera)
    : Component(gameObject)
    , m_isMainCamera(isMainCamera)
    , m_look(0.0f,0.1f,0.0f)
    , m_up(0.0f,0.1f,0.0f)
    , m_fovy(60.0f * 3.14f / 180)
    , m_aspect(16.0f / 9.0f)
    , m_near(0.1f)
    , m_far(1000.0f) {
    //----- カメラの登録
    CameraSystem::Get()->AddCamera(this);
}
// デストラクタ
CameraBase:: ~CameraBase(void) {
    //----- カメラの登録解除
    CameraSystem::Get()->DeleteCamera(this);
}


// ビュー行列の取得
const DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix(void) const {
    //------ 変数宣言
    DirectX::XMMATRIX view;     // ビュー行列
    auto pos = m_gameObject->GetTransform().pos;    // ゲームオブジェクトの座標

    //----- ビュー行列の取得
    view = DirectX::XMMatrixLookAtLH(
        DirectX::XMVectorSet(pos.x   , pos.y   , pos.z   , 0.0f),
        DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f), 
        DirectX::XMVectorSet(m_up.x  , m_up.y  , m_up.z  , 0.0f));

    //----- 返却用変数宣言
    DirectX::XMFLOAT4X4 ret;    // 返却用4x4配列

    //----- 返却
    view = DirectX::XMMatrixTranspose(view);    // 転置
    DirectX::XMStoreFloat4x4(&ret, view);       
    return ret; 
}
// プロジェクション行列の取得
const DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix(void) const {
    //----- 変数宣言
    DirectX::XMMATRIX proj; // プロジェクション行列

    //----- プロジェクション行列の取得
    proj = DirectX::XMMatrixPerspectiveFovLH(m_fovy, m_aspect, m_near, m_far);

    //----- 返却用変数宣言
    DirectX::XMFLOAT4X4 ret;

    proj = DirectX::XMMatrixTranspose(proj);    // 転置
    DirectX::XMStoreFloat4x4(&ret, proj);
    return ret;
}
