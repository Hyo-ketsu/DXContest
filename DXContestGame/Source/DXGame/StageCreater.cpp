#include <DXGame/StageCreater.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>  
#include <DXGame/Block.h>
#include <DXGame/Player.h>


const int CREATE_BLOCK_Z_COUNT = 100;   // 奥に生成する数
const int CREATE_BLOCK_X_COUNT = 5;     // 横に生成する数
const int CREATE_BLOCK_FRONT   = 5;     // プレイヤーの後ろに生成する数
const int CREATE_OBSTACLES_COUNT = 3;   // 障害物の生成数
const int CREATE_OBSTACLES_BACK_BLOCKCOUNT = 40;   // 奥のブロック何個目から生成するか
const float CREATE_BLOCK_Y_POS = 7;     // プレイヤーからどの位置に生成するか
const DirectX::XMFLOAT3 CREATE_BLOCK_SIZE     = { 2,2,2 };  // 生成ブロックのサイズ
const DirectX::XMFLOAT3 CREATE_OBSTACLES_SIZE = { 2,2,2 };  // 生成障害物のサイズ


void StageCreaterControl::Start(void) {
    //----- 変数初期化
    m_block.reserve(CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_X_COUNT);
    m_moveSpeed = 0;
    m_moveCount = 0;
    m_lastIndex = 0;
    
    //----- 開始座標設定
    m_firstPlayerTrans = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER)->GetTransform();
    m_firstPlayerTrans.pos.y -= CREATE_BLOCK_Y_POS;

    //----- ブロック生成
    for (int i = -(CREATE_BLOCK_FRONT); i < CREATE_BLOCK_Z_COUNT - CREATE_BLOCK_FRONT; i++) {
        for (int j = 0; j < CREATE_BLOCK_X_COUNT; j++) {
            //----- 座標設定
            Transform transform;
            transform.pos = m_firstPlayerTrans.pos;
            transform.pos.x += CREATE_BLOCK_SIZE.x * (j - (CREATE_BLOCK_X_COUNT / 1.5f));  // 開始座標を中心に生成
            transform.pos.z += CREATE_BLOCK_SIZE.z * i; // 開始座標から生成
            transform.size   = CREATE_BLOCK_SIZE;

            //----- 生成
            m_block.push_back(m_gameObject->GetScene()->CreatePrefab<Block>(transform));
        }
    }

    //----- 障害物生成
    CreateObstacles();
}
void StageCreaterControl::Update(void) {
    //----- 移動速度の加算
    m_moveSpeed += PlayerSpeedManager::Get()->GetSpeed();

    //----- ブロックの移動
    while (m_moveSpeed > CREATE_BLOCK_SIZE.z) {
        for (int i = 0; i < CREATE_BLOCK_X_COUNT; i++) {
            //----- ブロックの移動
            m_lastIndex = m_moveCount * CREATE_BLOCK_X_COUNT + i;
            auto transfrom = m_block[m_lastIndex]->GetTransform();
            transfrom.pos.z += CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_SIZE.z;
            m_block[m_lastIndex]->SetTransform(transfrom);
        }

        //----- カウントアップ
        m_moveCount++;
        if (m_moveCount >= CREATE_BLOCK_Z_COUNT) m_moveCount = 0;

        //----- 移動量減少
        m_moveSpeed -= CREATE_BLOCK_SIZE.z;
    }

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
                it = m_obstacles.erase(it);
            }
            else {
                //----- プレイヤーより前。イテレーターをインクリメント
                it++;
            }
        }
    }

    //----- 障害物の生成
    if (m_obstacles.size() < CREATE_OBSTACLES_COUNT) {
        //----- サイズ分不足している。生成
        int size = m_obstacles.size();
        m_obstacles.resize(CREATE_OBSTACLES_COUNT);
        for (int i = size; i < CREATE_OBSTACLES_COUNT; i++) {
            //----- 座標の設定
            Transform transform = m_block[m_lastIndex]->GetTransform();
            transform.pos.x = CREATE_BLOCK_SIZE.x * CREATE_BLOCK_X_COUNT * ((rand() % 100 - 100 / 2) * 0.01f);
            transform.pos.y += CREATE_BLOCK_Y_POS;
            transform.pos.z -= CREATE_BLOCK_SIZE.z * (rand() % CREATE_OBSTACLES_BACK_BLOCKCOUNT);
            transform.size = CREATE_OBSTACLES_SIZE;

            //----- 生成
            m_obstacles[i] = m_gameObject->GetScene()->CreatePrefab<Obstacles>(transform);
        }
    }
}


void StageCreater::Prefab(void) {
    AddComponent<StageCreaterControl>();
}
     