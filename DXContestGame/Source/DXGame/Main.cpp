#include <DXGame/Main.h>
#include <DirectXTex/Texture.h>
#include <DXGame/DirectX.h>
#include <DXGame/WinUtil.h>
#include <DXGame/Input.h>
#include <DXGame/Game3D.h>
#include <DXGame/Geometory.h>
#include <DXGame/Sprite.h>

//--- 定数定義
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

//-- グローバル変数
Game3D* g_pGame;

// 度数（゜）をラジアンに変換する式
const float GetRad(const float rad) {
    return rad * 3.14f / 180;
}

unsigned int GetAppWidth(void) {
	return SCREEN_WIDTH;
}
unsigned int GetAppHeight(void) {
	return SCREEN_HEIGHT;
}

void Init(void) {
	if (FAILED(InitDX(GetHWND(), SCREEN_WIDTH, SCREEN_HEIGHT, false)))
	{
		Error("directx initialize failed.");
	}
	if (FAILED(InitTexture(GetDevice())))
	{
		Error("texture initialize failed.");
	}
	if (FAILED(InitInput()))
	{
		Error("input initialize failed.");
	}
	if (FAILED(InitGeometory()))
	{
		Error("geometory initialize failed.");
	}

    Sprite::Init();

	g_pGame = new Game3D();
}
void Uninit()
{
	delete g_pGame;
    Sprite::Uninit();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void Update(float deltaTime)
{
	UpdateInput();
	g_pGame->Update();
}
void Draw()
{
	BeginDrawDX();
	g_pGame->Draw();
	EndDrawDX();
}
