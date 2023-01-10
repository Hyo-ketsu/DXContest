#include <DXGame/Stage1.h>
#include <DXGame/StageCreater.h>
#include <DXGame/GameCamera.h>
#include <DXGame/Player.h>
#include <DXGame/Score.h>


void Stage1::InitScene(void) {
    CreatePrefab<Score>(Transform(DirectX::XMFLOAT3(-0.9f, 0.9f, 0), DirectX::XMFLOAT3(0.1f, 0.1f, -1)));
    CreatePrefab<StageCreater>();
    CreatePrefab<Player>();
    CreatePrefab<GameCamera>(Transform(DirectX::XMFLOAT3(0.f,5.f,15.f)));
}
