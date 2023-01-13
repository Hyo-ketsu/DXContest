#include <DXGame/StageCreater.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>  
#include <DXGame/Block.h>
#include <DXGame/Player.h>
#include <DXGame/Obstacles.h>
#include <DXGame/Utility.h>


const int CREATE_BLOCK_Z_COUNT = 80;   // 奥に生成する数
const int CREATE_BLOCK_X_COUNT = 9;    // 横に生成する数
const int CREATE_BLOCK_FRONT   = 5;    // プレイヤーの後ろに生成する数
const int CREATE_OBSTACLES_COUNT = 50; // 障害物の生成数
const int CREATE_OBSTACLES_FLAME_MAX = 45; // 障害物生成最長フレーム数
const int CREATE_OBSTACLES_FLAME_MIN = 4;  // 障害物生成最短フレーム数
const int CREATE_OBSTACLES_BACK_BLOCKCOUNT = 70;    // 奥のブロック何個目から生成するか
const float CREATE_BLOCK_Y_POS = 7;                 // プレイヤーからどの位置に生成するか
const DirectX::XMFLOAT3 CREATE_BLOCK_SIZE      = { 2,2,2 };  // 生成ブロックのサイズ
const DirectX::XMFLOAT3 CREATE_BLOCK_SPACE     = { 5,0,5 };  // 生成ブロックの生成間隔
const DirectX::XMFLOAT3 CREATE_OBSTACLES_SIZE  = { 2,2,2 };  // 生成障害物のサイズ
const DirectX::XMFLOAT3 CREATE_OBSTACLES_SPACE = { 2.5f,0,0 };  // 生成障害物の生成間隔


void StageCreaterControl::Start(void) {
    //----- 変数初期化
    m_block.reserve(CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_X_COUNT);
    m_moveSpeed = 0;
    m_moveCount = 0;
    m_lastIndex = 0;
    m_obstaclesFlame = 0;
    
    //----- 開始座標設定
    m_firstPlayerTrans = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER)->GetTransform();
    m_firstPlayerTrans.pos.y -= CREATE_BLOCK_Y_POS;

    //----- ブロック生成
    for (int i = -(CREATE_BLOCK_FRONT); i < CREATE_BLOCK_Z_COUNT - CREATE_BLOCK_FRONT; i++) {
        for (int j = 0; j < CREATE_BLOCK_X_COUNT; j++) {
            //----- 座標設定
            Transform transform;
            transform.pos = m_firstPlayerTrans.pos;
            transform.pos.x += CREATE_BLOCK_SPACE.x * (j - (CREATE_BLOCK_X_COUNT / 2));  // 開始座標を中心に生成
            transform.pos.z += CREATE_BLOCK_SPACE.z * i; // 開始座標から生成
            transform.size   = CREATE_BLOCK_SIZE;

            //----- 生成
            m_block.push_back(m_gameObject->GetScene()->CreatePrefab<Block>(transform));
        }
    }

    //----- 障害物生成
    CreateObstacles();
}
void StageCreaterControl::Update(void) {
    //----- プレイヤーが削除されていたら処理をしない
    if (SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER) == nullptr) return;

    //----- 移動速度の加算
    m_moveSpeed += PlayerSpeedManager::Get()->GetSpeed();

    //----- ブロックの移動
    while (m_moveSpeed > CREATE_BLOCK_SPACE.z) {
        for (int i = 0; i < CREATE_BLOCK_X_COUNT; i++) {
            //----- ブロックの移動
            m_lastIndex = m_moveCount * CREATE_BLOCK_X_COUNT + i;
            auto transfrom = m_block[m_lastIndex]->GetTransform();
            transfrom.pos.z += CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_SPACE.z;
            m_block[m_lastIndex]->SetTransform(transfrom);
        }

        //----- カウントアップ
        m_moveCount++;
        if (m_moveCount >= CREATE_BLOCK_Z_COUNT) m_moveCount = 0;

        //----- 移動量減少
        m_moveSpeed -= CREATE_BLOCK_SPACE.z;
    }

    //----- 障害物用カウンターアップ（正確にはダウン）
    m_obstaclesFlame--;

    //----- 障害物設定
    CreateObstacles();
}


// 障害物を生成する
void StageCreaterControl::CreateObstacles(void) {
    //----- プレイヤーの後ろに移った障害物の削除
    if (m_obstacles.empty() == false) {
        for (auto it = m_obstacles.begin(); it != m_obstacles.end();) {
            if (m_block[m_moveCount * CREATE_BLOCK_X_COUNT]->GetTransform().pos.z >= (*it)->GetTransform().pos.z) {
                //----- 最後尾のブロックより（障害物の位置が）後ろ（-Z）。削除
                (*it)->DeleteGameObject();
                it = m_obstacles.erase(it);
            }
            else {
                //----- プレイヤーより前。イテレーターをインクリメント
                it++;
            }
        }
    }

    //----- 障害物の生成
    if (m_obstaclesFlame < 0) { // 生成できるフレームになっているか
        if (m_obstacles.size() < CREATE_OBSTACLES_COUNT) {  // 生成する余裕があるか
            //----- 生成が可能。生成
            //----- 座標の設定
            Transform transform = m_block[m_lastIndex]->GetTransform();
            transform.pos.x  = CREATE_OBSTACLES_SPACE.x * CREATE_BLOCK_X_COUNT * ((rand() % 100 - 100 / 2) * 0.02f);
            transform.pos.y += CREATE_BLOCK_Y_POS;
            transform.pos.z;
            transform.size = CREATE_OBSTACLES_SIZE;

            //----- 生成
            m_obstacles.push_back(m_gameObject->GetScene()->CreatePrefab<Obstacles>(transform));
        }

        //----- カウンターのリセット
        do {
            //----- 変数宣言
            float speed = PlayerSpeedManager::Get()->GetSpeed();    // プレイヤーの速度

            //----- 速度が0.f以外か（ガード節）
            if (Utility::FloatComparison(speed)) {
                //----- プレイヤーの速度が0。生成フレーム数に最長値を代入して終了
                m_obstaclesFlame = CREATE_OBSTACLES_FLAME_MAX;
                break;
            }

            //----- 変数宣言
            unsigned int count = CREATE_OBSTACLES_FLAME_MAX / speed;    // 生成フレームカウント

            //----- カウント数が0以外か
            if (count == 0) {
                //----- カウント数が0。出現フレーム数に最低値を格納、終了
                m_obstaclesFlame = CREATE_OBSTACLES_FLAME_MIN;
                break;
            }

            //----- 出現フレームランダム設定
            m_obstaclesFlame = rand() % count;

            //----- 最低値保障
            if (m_obstaclesFlame < CREATE_OBSTACLES_FLAME_MIN) {
                //----- 最低値未満。最低値を代入
                m_obstaclesFlame = CREATE_OBSTACLES_FLAME_MIN;
            }
        } while (false);
    }
}


void StageCreater::Prefab(void) {
    AddComponent<StageCreaterControl>();
}
     