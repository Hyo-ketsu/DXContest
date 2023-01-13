#include <DXGame/DirectXTex/Texture.h>
#include <DXGame/DirectX.h>
#include <DXGame/WinUtil.h>
#include <DXGame/Input.h>
#include <DXGame/Geometory.h>
#include <DXGame/Sprite.h>
#include <DXGame/GameApplication.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/WinUtil.h>
#include <DXGame/Timer.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/Title.h>
#include <DXGame/GameApplication.h>
#include <DXGame/AssetsLoad.h>
#include <DXGame/Sound.h>
#include <DXGame/SoundComponent.h>
#include <time.h>


//--- 定数定義
const char* APP_TITLE = "DX2D";

void Init(void);
void Uninit(void);


// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#ifdef _DEBUG
    //----- メモリリークチェック
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // _DEBUG

    //----- ウィンドウの初期化
    GameApplication::Get()->SetWindowSizeX(SCREEN_X);
    GameApplication::Get()->SetWindowSizeY(SCREEN_Y);
    if (FAILED(InitWindow(APP_TITLE, GameApplication::Get()->GetWindowSizeX(), GameApplication::Get()->GetWindowSizeY()))) {
        Error("window initialize faield");
    }

    //----- DirectX等の初期化
    Init();

    //----- 初期シーン設定
    SceneLoader::Get()->MoveScene<Title>();

    //----- 変数宣言
    Timer timer;
    AppState state = APP_STATE_MESSAGE;

    //----- 初期音量設定
#ifdef _DEBUG
    SoundVolumeSetter::Get()->SetBGMVolume(0.f);
    SoundVolumeSetter::Get()->SetSEVolume(0.f);
#else
    SoundVolumeSetter::Get()->SetBGMVolume(1.f);
    SoundVolumeSetter::Get()->SetSEVolume(1.f);
#endif // !_DEBUG

    //----- ゲームループ
    while (1) {
        //----- ゲームの終了
        if (state == APP_STATE_QUIT)              break; // ウィンドウが閉じられる等したか
        if (GameApplication::Get()->GetGameEnd()) break; // ゲームが終了しているか

        //----- ウィンドウメッセージ取得
        state = UpdateWindow();

        //----- 更新
        Timer::UpdateTime();

        //----- ゲームループ
        // 1フレーム（1/60秒）経っている、かつウィンドウが更新できる（閉じられたり等されていない）か
        if (timer.IsFpsCheck() && state == APP_STATE_WAIT) {
            //----- キー入力更新
            UpdateInput();

            //----- 更新処理
            SceneLoader::Get()->Update();

            //----- 描画処理
            SceneLoader::Get()->Draw();
        }
    }

    //----- 終了処理
    Uninit();
    UninitWindow();
    return 0;
}




void Init(void) {
	if (FAILED(InitDX(GetHWND(), GameApplication::Get()->GetWindowSizeX(), GameApplication::Get()->GetWindowSizeY(), false))) {
		Error("directx initialize failed.");
	}
	if (FAILED(InitTexture(GetDevice()))) {
		Error("texture initialize failed.");
	}
	if (FAILED(InitInput())) {
		Error("input initialize failed.");
	}
	if (FAILED(InitGeometory())) {
		Error("geometory initialize failed.");
	}
    if (FAILED(InitSound())) {
        Error("sound initialize failed.");
    }

    //----- 乱数初期化
    srand((unsigned int)timeGetTime());
    for (int i = 0; i < 100; i++) {
        //----- 空回し
        rand();
    }

    Sprite::Init();
    Timer::InitTime();
    SceneLoader::Get()->DeleteScene();
    //FirstLoad();
}
void Uninit(void) {
    SceneLoader::DeleteInstance();
    Timer::UninitTime();
    UninitSound();
    Sprite::Uninit();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
