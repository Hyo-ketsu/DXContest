#ifndef __GAME_3D_H__
#define __GAME_3D_H__

#include "Model.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "CameraBase.h"
#include "Stage.h"
#include "Player.h"
#include "CameraPlayer.h"
#include "BlendState.h"
#include "GameUI.h"


enum CameraKind {
    CAM_PLAYER,
    CAM_DEBUG,
    CAM_EVENT,
    MAX_CAMERA, // camera�ő吔
};


class Game3D {
public:
	Game3D();
	~Game3D();

	void Update();
	void Draw();

private:
    VertexShader* m_pModelVS;
    ConstantBuffer* m_pWVP;
    Player* m_pPlayer;
    Stage m_stage;
    CameraBase* m_pCamera[MAX_CAMERA];
    CameraKind m_mainCamera;
    BlendState* m_pBlend;
    GameUI* m_pUI;
};

#endif // __GAME_3D_H__