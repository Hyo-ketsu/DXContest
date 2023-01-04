//#include "Game3D.h"
//#include <memory>
//#include "Geometory.h"
//#include "Model.h"
//#include "CameraDebug.h"
//#include "CameraEvent.h"
//#include "Input.h"
//#include "Collsion.h"
//
//
//Game3D::Game3D()
//{
//    //----- 頂点シェーダーの読み込み
//    m_pModelVS = new VertexShader;
//    if (FAILED(m_pModelVS->Load("Assets/Shader/ModelVS.cso"))) {
//        MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
//    }
//
//    //----- 頂点シェーダーの設定
//    //g_unityChan->SetVertexShader(m_pModelVS);
//
//    //----- コンスタントバッファーの読み込み
//    m_pWVP = new ConstantBuffer();
//    m_pWVP->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
//
//    //----- プレイヤー初期化
//    m_pPlayer = new Player();
//
//    //----- カメラ作成
//    m_mainCamera = CAM_EVENT;
//    m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer);
//    m_pCamera[CAM_DEBUG]  = new CameraDebug();
//    CameraEvent* pEvent   = new CameraEvent();
//    pEvent->SetEvent({ 0,0,0 }, { -4,4,-7 }, 1);
//    m_pCamera[CAM_EVENT] = pEvent;
//
//    m_pPlayer->SetCamera(m_pCamera[CAM_PLAYER]);
//
//    //----- カメラ作成
//    //m_pCamera = new CameraDebug();
//
//    //----- 画像合成の方法
//    m_pBlend = new BlendState;
//    D3D11_RENDER_TARGET_BLEND_DESC blend = {};
//    blend.BlendEnable = TRUE;
//    blend.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//    blend.SrcBlend = D3D11_BLEND_SRC_ALPHA;
//    blend.SrcBlendAlpha = D3D11_BLEND_ONE;
//    blend.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//    blend.DestBlendAlpha = D3D11_BLEND_ONE;
//    blend.BlendOp = D3D11_BLEND_OP_ADD;
//    blend.BlendOpAlpha = D3D11_BLEND_OP_ADD;
//
//    m_pBlend->Create(blend);
//    m_pBlend->Bind();
//
//    m_pUI = new GameUI();
//}
//Game3D::~Game3D()
//{
//    delete m_pUI;
//    if (m_pPlayer != nullptr) {
//        delete m_pPlayer;
//        m_pPlayer = nullptr;
//    }
//
//    for (int i = 0; i < MAX_CAMERA; i++) {
//        delete m_pCamera[i];
//    } 
//}
//void Game3D::Update()
//{
//    // 更新
//    if (m_mainCamera == CAM_PLAYER) m_pPlayer->Update();
//    m_pCamera[m_mainCamera]->Update();
//
//    CameraKind camera = m_mainCamera;
//    if (IsKeyPress('C')) {
//        if (IsKeyTrigger('1')) camera = CAM_PLAYER;
//        if (IsKeyTrigger('2')) camera = CAM_DEBUG;
//        if (IsKeyTrigger('3')) {
//            CameraEvent* pEvent = dynamic_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
//            pEvent->SetEvent({ 0,0,0 }, { -4,4,-7 }, 8);
//            camera = CAM_EVENT;
//        }
//    }
//    if (m_mainCamera != camera) {
//        m_mainCamera = camera;
//        m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
//    }
//
//    if (m_mainCamera == CAM_EVENT) {
//        CameraEvent* pEvent = dynamic_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
//        if (!(pEvent->IsEvent())) {
//            m_mainCamera = CAM_PLAYER;
//            m_pPlayer->SetCamera(m_pCamera[m_mainCamera]);
//        }
//    }
//
//    //----- 当たり判定処理
//    for (int i = 0; i < m_stage.GetBlockNum(); i++) {
//        Stage::Info     block = m_stage.GetBloackInfo(i);
//        Stage::Vertices vtx   = m_stage.GetBloackVertices(i);
//
//        // 面の法線を計算
//        DirectX::XMFLOAT3 planeN = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
//
//        // 当たり判定
//        Collision::Plane plane = { planeN,block.pos  };
//        Collision::Ray ray = { m_pPlayer->GetPos(),{0,-0.01f,0},1 };
//        Collision::Result result = Collision::CheckRayPlane(ray, plane);
//        if (result.hit) {
//            //Collision::Triangle triangle[2] = { { vtx.pos[0],vtx.pos[1],vtx.pos[2]},{vtx.pos[2],vtx.pos[1],vtx.pos[3]}, };
//            //DirectX::XMFLOAT3 point = result.point;
//            //for (int j = 0; j < 2; j++) {
//                //result = Collision::CheckPointTraiangle(point, triangle[j]);
//                if (result.hit) {
//                    m_pPlayer->Landing(result, plane);
//                    break;
//                }
//            //}
//        }
//    }
//}
//void Game3D::Draw()
//{
//    DirectX::XMVECTOR eyePos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//    DirectX::XMVECTOR focusPos = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
//    DirectX::XMVECTOR upPos = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//    const float fovAngleY = 60.0f * 3.14f / 180;
//    const float asepectRatio = 16.0f / 9.0f;
//    const float nearZ = 0.1f;
//    const float FarZ = 1000.0f;
//
//    DirectX::XMFLOAT4X4 mat[3];
//
//    //----- ワールド変換行列
//    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
//    DirectX::XMMATRIX Rx = DirectX::XMMatrixRotationX(0.0f);
//    DirectX::XMMATRIX Ry = DirectX::XMMatrixRotationY(0.0f);
//    DirectX::XMMATRIX Rz = DirectX::XMMatrixRotationZ(0.0f);
//    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
//    DirectX::XMMATRIX world = S * Rx * Ry * Rz * T;
//    world = DirectX::XMMatrixTranspose(world);
//    DirectX::XMStoreFloat4x4(&mat[0], world);
//
//    //----- ビュー変換行列
//    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(eyePos, focusPos, upPos);
//    view = DirectX::XMMatrixTranspose(view);
//    DirectX::XMStoreFloat4x4(&mat[1], view);
//
//    //----- プロジェクション変換行列
//    DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(fovAngleY, asepectRatio, nearZ, FarZ);
//    proj = DirectX::XMMatrixTranspose(proj);
//    DirectX::XMStoreFloat4x4(&mat[2], proj);
//
//    //----- カメラパラメーターにて置き換え
//    if (m_pCamera != nullptr) {
//        mat[1] = m_pCamera[m_mainCamera]->GetViewMatrix();
//        mat[2] = m_pCamera[m_mainCamera]->GetProjectionMatrix();
//    }
//
//    m_pWVP->Write(mat);
//    m_pWVP->BindVS(0);
//
//    SetGeometoryVPMatrix(
//        m_pCamera[m_mainCamera]->GetViewMatrix(),
//        m_pCamera[m_mainCamera]->GetProjectionMatrix()
//    );
//    DrawBox();
//
//    m_stage.Draw();
//
//    m_pPlayer->Draw();
//
//    EnableDepth(false);
//    m_pUI->Draw();
//    EnableDepth(true);
//}
