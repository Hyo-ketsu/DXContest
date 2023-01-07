#include <DXGame/Stage1.h>
#include <DXGame/Block.h>
#include <DXGame/GameCamera.h>


void Stage1::InitScene(void) {
    CreatePrefab<Block>();
    CreatePrefab<GameCamera>(Transform(DirectX::XMFLOAT3(0.f,-3.f,-10.f)));
}
