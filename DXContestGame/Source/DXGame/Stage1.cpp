#include <DXGame/Stage1.h>
#include <DXGame/StageCreater.h>
#include <DXGame/GameCamera.h>
#include <DXGame/Player.h>
#include <DXGame/Score.h>
#include <DXGame/SoundComponent.h>
#include <DXGame/GameDefine.h>


void Stage1::InitScene(void) {
    //----- �Q�[���I�u�W�F�N�g�ǉ�
    CreatePrefab<Score>(Transform(DirectX::XMFLOAT3(-0.9f, 0.9f, 0), DirectX::XMFLOAT3(0.1f, 0.1f, -1)));
    CreatePrefab<StageCreater>();
    CreatePrefab<Player>();
    CreatePrefab<GameCamera>(Transform(DirectX::XMFLOAT3(0.f,5.f,15.f)));

    //----- �T�E���h�Đ��p�Q�[���I�u�W�F�N�g�ǉ�
    auto gameObject = CreatePrefab<GameObject>();
    auto sound = new SoundComponent(gameObject, LOAD_STAGE_BGM, true);
    gameObject->AddComponent(sound);
    sound->StartSound();
}
