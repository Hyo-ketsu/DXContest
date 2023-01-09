#include <DXGame/Player.h>
#include <DXGame/GameDefine.h>
#include <DXGame/HP.h>
#include <DXGame/Input.h>
#include <DXGame/ModelComponent.h>
#include <DXGame/CameraSystem.h>
#include <DXGame/CameraBase.h>
#include <DXGame/FileStorage.h>
#include <DXGame/Collsion.h>


const float PLAYER_AUTO_MOVE_SPEED_DEFAULT = 0.25f;     // 前方への移動速度
const float PLAYER_AUTO_MOVE_SPEED_ADD     = 0.00001f;  // 前方への移動速度加速値
const float PLAYER_MOVE_SPEED      = 0.2f; // プレイヤーの左右への移動速度
const float PLAYER_MOVE_MAX        = 2.0f;  // 左右移動上限
const std::string PLAYER_FILENAME = "Unitychan/unitychan.fbx";  // 読み込みファイル名


void PlayerControl::Start(void) {
    //----- 速度初期化
    PlayerSpeedManager::Get()->SetSpeed(PLAYER_AUTO_MOVE_SPEED_DEFAULT);

    //----- Polyline初期化
    m_polyline = std::unique_ptr<GeometoryPolyline>(new GeometoryPolyline(30));
    m_polyline->SetTexture(FileStorage::Get()->LoadTexture("Foo.png"));
}
void PlayerControl::Update(void) {
    //----- 左右移動
    // 左移動
    if (IsKeyPress('A') || IsKeyPress(VK_LEFT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x -= PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }
    // 右移動
    if (IsKeyPress('D') || IsKeyPress(VK_RIGHT)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x += PLAYER_MOVE_SPEED;
        m_gameObject->SetTransform(pos);
    }

    //----- 左右移動上限補正
    // 左補正
    if (m_gameObject->GetTransform().pos.x < -(PLAYER_MOVE_MAX)) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x = -(PLAYER_MOVE_MAX);
        m_gameObject->SetTransform(pos);
    }
    // 右補正
    if (m_gameObject->GetTransform().pos.x >   PLAYER_MOVE_MAX ) {
        auto pos = m_gameObject->GetTransform();
        pos.pos.x =   PLAYER_MOVE_MAX ;
        m_gameObject->SetTransform(pos);
    }

    //----- 前進
    {
        auto pos = m_gameObject->GetTransform();
        pos.pos.z += PlayerSpeedManager::Get()->GetSpeed();
        m_gameObject->SetTransform(pos);
    }

    //----- 加速
    PlayerSpeedManager::Get()->SetSpeed(PlayerSpeedManager::Get()->GetSpeed() + PLAYER_AUTO_MOVE_SPEED_ADD);

    //----- 自身が死亡していたら削除
    if (m_gameObject->GetComponent<HP>()->IsDead()) {
        PlayerSpeedManager::Get()->SetSpeed(0.f);
        m_gameObject->DeleteGameObject();
    }
}
void PlayerControl::Collsion(void) {
    auto data = m_gameObject->GetCollsionData();
    for (auto& it : data.list) {
        if (it.hitCollsion->GetTag() == Tag::Ground) {
            m_gameObject->GetComponent<HP>()->Damage(m_gameObject->GetComponent<HP>()->GetHP());
        }
    }
}
void PlayerControl::Draw(void) {
    //----- ポリラインのポイント追加
    GeometoryPolyline::Point point;
    point.pos = m_gameObject->GetTransform().pos;  // プレイヤーの位置
    point.width = 0.3f; // ポリラインの幅

    //----- カメラに向かう法線を計算
    m_polyline->PushPoint(point);
    DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&CameraSystem::Get()->GetCamera()->GetGameObject()->GetTransform().pos);
    DirectX::XMVECTOR vPos = DirectX::XMLoadFloat3(&m_gameObject->GetTransform().pos);
    DirectX::XMStoreFloat3(&point.normal, DirectX::XMVectorSubtract(vCamPos, vPos));
    m_polyline->PushPoint(point);
    //----- ポリラインの表示
    m_polyline->SetView(CameraSystem::Get()->GetCamera()->GetViewMatrix());
    m_polyline->SetProjection(CameraSystem::Get()->GetCamera()->GetProjectionMatrix());
    m_polyline->Draw();
}


void Player::Prefab(void) {
    //----- オブジェクト設定
    SetName(NAME_PLAYER);

    //----- 当たり判定の追加
    AddCollsion(false, DirectX::XMFLOAT3(3, 5, 3));

    //----- モデルコンポーネントの追加
    auto* model = new ModelComponent(this, PLAYER_FILENAME, 0.05f);

    //----- コンポーネントの追加
    AddComponent(model);
    AddComponent<HP>();
    AddComponent<PlayerControl>();
}
