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
#include <DXGame/Stage1.h>
#include <DXGame/GameApplication.h>
#include <DXGame/AssetsLoad.h>
#include <time.h>


//--- �萔��`
const char* APP_TITLE = "DX2D";

void Init(void);
void Uninit(void);
void Update(void);
void Draw(void);


// �G���g���|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    //----- �E�B���h�E�̏�����
    GameApplication::Get()->SetWindowSizeX(SCREEN_X);
    GameApplication::Get()->SetWindowSizeY(SCREEN_Y);
    if (FAILED(InitWindow(APP_TITLE, GameApplication::Get()->GetWindowSizeX(), GameApplication::Get()->GetWindowSizeY()))) {
        Error("window initialize faield");
    }

    //----- DirectX���̏�����
    Init();

    //----- �����V�[���ݒ�
    SceneLoader::Get()->MoveScene<Stage1>();

    //----- �ϐ��錾
    Timer timer;
    AppState state = APP_STATE_MESSAGE;

    //----- �Q�[�����[�v
    while (1) {
        //----- �Q�[���̏I��
        if (state == APP_STATE_QUIT)              break; // �E�B���h�E�������铙������
        if (GameApplication::Get()->GetGameEnd()) break; // �Q�[�����I�����Ă��邩

        //----- �E�B���h�E���b�Z�[�W�擾
        state = UpdateWindow();

        //----- �X�V
        Update();

        //----- �Q�[�����[�v
        // 1�t���[���i1/60�b�j�o���Ă���A���E�B���h�E���X�V�ł���i����ꂽ�蓙����Ă��Ȃ��j��
        if (timer.IsFpsCheck() && state == APP_STATE_WAIT) {
            SceneLoader::Get()->Update();
            SceneLoader::Get()->Draw();
        }
    }

    //----- �I������
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

    //----- ����������
    srand((unsigned int)timeGetTime());
    for (int i = 0; i < 100; i++) {
        //----- ���
        rand();
    }

    Sprite::Init();
    Timer::InitTime();
    SceneLoader::Get()->DeleteScene();
    FirstLoad();
}
void Uninit(void) {
    Timer::UninitTime();
    Sprite::Uninit();
    SceneLoader::DeleteInstance();
	UninitGeometory();
	UninitInput();
	UninitTexture();
	UninitDX();
}
void Update(void) {
	UpdateInput();
    Timer::UpdateTime();
}
