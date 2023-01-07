#include <DXGame/ModelComponent.h>
#include <DXGame/FileStorage.h>
#include <DXGame/CameraSystem.h>
#include <DXGame/GameObject.h>


// コンストラクタ
ModelComponent::ModelComponent(GameObject* gameObject, const std::string& fileName, const float scale, const float flip)
    : Component(gameObject) 
    , m_model(std::unique_ptr<Model>(FileStorage::Get()->LoadModel(fileName, scale, flip)))
    , m_wvp(std::make_unique<ConstantBuffer>()) {
    m_wvp->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}


// 初期化処理
void ModelComponent::Start(void) {
}
// 描画処理
void ModelComponent::Draw(void) {
    DirectX::XMFLOAT4X4 mat[3];
    DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(m_gameObject->GetTransform().pos.x, m_gameObject->GetTransform().pos.y, m_gameObject->GetTransform().pos.z)));
    mat[1] = CameraSystem::Get()->GetCamera()->GetViewMatrix();
    mat[2] = CameraSystem::Get()->GetCamera()->GetProjectionMatrix();
    m_wvp->Write(mat);
    m_wvp->BindVS(0);
    m_model->Draw();
}
