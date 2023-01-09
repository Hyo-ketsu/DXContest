#include <DXGame/Stage1.h>
#include <DXGame/StageCreater.h>
#include <DXGame/GameCamera.h>
#include <DXGame/Player.h>


void Stage1::InitScene(void) {
    CreatePrefab<StageCreater>();
    CreatePrefab<Player>();
    CreatePrefab<GameCamera>(Transform(DirectX::XMFLOAT3(0.f,5.f,15.f)));
}
