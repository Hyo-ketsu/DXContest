#include <DXGame/StageCreater.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/GameDefine.h>  
#include <DXGame/Block.h>
#include <DXGame/Player.h>


const int CREATE_BLOCK_Z_COUNT = 80;   // ���ɐ������鐔
const int CREATE_BLOCK_X_COUNT = 7;    // ���ɐ������鐔
const int CREATE_BLOCK_FRONT   = 5;    // �v���C���[�̌��ɐ������鐔
const int CREATE_OBSTACLES_COUNT = 20; // ��Q���̐�����
const int CREATE_OBSTACLES_FLAME = 60; // ��Q�������Œ��t���[����
const int CREATE_OBSTACLES_BACK_BLOCKCOUNT = 70;    // ���̃u���b�N���ڂ��琶�����邩
const float CREATE_BLOCK_Y_POS = 7;                 // �v���C���[����ǂ̈ʒu�ɐ������邩
const DirectX::XMFLOAT3 CREATE_BLOCK_SIZE      = { 2,2,2 };  // �����u���b�N�̃T�C�Y
const DirectX::XMFLOAT3 CREATE_BLOCK_SPACE     = { 5,0,5 };  // �����u���b�N�̐����Ԋu
const DirectX::XMFLOAT3 CREATE_OBSTACLES_SIZE  = { 2,2,2 };  // ������Q���̃T�C�Y
const DirectX::XMFLOAT3 CREATE_OBSTACLES_SPACE = { 4,0,0 };  // ������Q���̐����Ԋu


void StageCreaterControl::Start(void) {
    //----- �ϐ�������
    m_block.reserve(CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_X_COUNT);
    m_moveSpeed = 0;
    m_moveCount = 0;
    m_lastIndex = 0;
    m_obstaclesFlame = 0;
    
    //----- �J�n���W�ݒ�
    m_firstPlayerTrans = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER)->GetTransform();
    m_firstPlayerTrans.pos.y -= CREATE_BLOCK_Y_POS;

    //----- �u���b�N����
    for (int i = -(CREATE_BLOCK_FRONT); i < CREATE_BLOCK_Z_COUNT - CREATE_BLOCK_FRONT; i++) {
        for (int j = 0; j < CREATE_BLOCK_X_COUNT; j++) {
            //----- ���W�ݒ�
            Transform transform;
            transform.pos = m_firstPlayerTrans.pos;
            transform.pos.x += CREATE_BLOCK_SPACE.x * (j - (CREATE_BLOCK_X_COUNT / 2));  // �J�n���W�𒆐S�ɐ���
            transform.pos.z += CREATE_BLOCK_SPACE.z * i; // �J�n���W���琶��
            transform.size   = CREATE_BLOCK_SIZE;

            //----- ����
            m_block.push_back(m_gameObject->GetScene()->CreatePrefab<Block>(transform));
        }
    }

    //----- ��Q������
    CreateObstacles();
}
void StageCreaterControl::Update(void) {
    //----- �v���C���[���������Ă��Ȃ���Ώ��������Ȃ�
    if (SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER) == nullptr) return;

    //----- �ړ����x�̉��Z
    m_moveSpeed += PlayerSpeedManager::Get()->GetSpeed();

    //----- �u���b�N�̈ړ�
    while (m_moveSpeed > CREATE_BLOCK_SPACE.z) {
        for (int i = 0; i < CREATE_BLOCK_X_COUNT; i++) {
            //----- �u���b�N�̈ړ�
            m_lastIndex = m_moveCount * CREATE_BLOCK_X_COUNT + i;
            auto transfrom = m_block[m_lastIndex]->GetTransform();
            transfrom.pos.z += CREATE_BLOCK_Z_COUNT * CREATE_BLOCK_SPACE.z;
            m_block[m_lastIndex]->SetTransform(transfrom);
        }

        //----- �J�E���g�A�b�v
        m_moveCount++;
        if (m_moveCount >= CREATE_BLOCK_Z_COUNT) m_moveCount = 0;

        //----- �ړ��ʌ���
        m_moveSpeed -= CREATE_BLOCK_SPACE.z;
    }

    //----- ��Q���p�J�E���^�[�A�b�v�i���m�ɂ̓_�E���j
    m_obstaclesFlame--;

    //----- ��Q���ݒ�
    CreateObstacles();
}


// ��Q���𐶐�����
void StageCreaterControl::CreateObstacles(void) {
    //----- �v���C���[�̌��Ɉڂ�����Q���̍폜
    if (m_obstacles.empty() == false) {
        for (auto it = m_obstacles.begin(); it != m_obstacles.end();) {
            if (m_block[m_moveCount * CREATE_BLOCK_X_COUNT]->GetTransform().pos.z >= (*it)->GetTransform().pos.z) {
                //----- �Ō���̃u���b�N���i��Q���̈ʒu���j���i-Z�j�B�폜
                it = m_obstacles.erase(it);
            }
            else {
                //----- �v���C���[���O�B�C�e���[�^�[���C���N�������g
                it++;
            }
        }
    }

    //----- ��Q���̐���
    if (m_obstaclesFlame < 0) { // �����ł���t���[���ɂȂ��Ă��邩
        if (m_obstacles.size() < CREATE_OBSTACLES_COUNT) {  // ��������]�T�����邩
            //----- �������\�B����
            //----- ���W�̐ݒ�
            Transform transform = m_block[m_lastIndex]->GetTransform();
            transform.pos.x  = CREATE_OBSTACLES_SPACE.x * CREATE_BLOCK_X_COUNT * ((rand() % 100 - 100 / 2) * 0.02f);
            transform.pos.y += CREATE_BLOCK_Y_POS;
            transform.pos.z;
            transform.size = CREATE_OBSTACLES_SIZE;

            //----- ����
            m_obstacles.push_back(m_gameObject->GetScene()->CreatePrefab<Obstacles>(transform));
        }

        //----- �J�E���^�[�̃��Z�b�g
        m_obstaclesFlame = rand() % CREATE_OBSTACLES_FLAME;
    }
}


void StageCreater::Prefab(void) {
    AddComponent<StageCreaterControl>();
}
     