#include <DXGame/Stage1.h>
#include <DXGame/Block.h>
#include <DXGame/GameCamera.h>


void Stage1::InitScene(void) {
    CreatePrefab<Block>(Transform(DirectX::XMFLOAT3(0.f, 0.f, 0.f),DirectX::XMFLOAT3(10.f,10.f,10.f)));
    CreatePrefab<GameCamera>(Transform(DirectX::XMFLOAT3(0.f,5.f,15.f)));
}
