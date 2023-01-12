#include <DXGame/AssetsLoad.h>
#include <thread>
#include <DXGame/FileStorage.h>
#include <DXGame/GameDefine.h>


const int LOAD_ASSETS_SPRITE_COUNT = 32;    // �ǂݍ��ݎ��̍ő啪����


// �ǂ̃t�@�C���A���ǂݍ��ނ��̏����i�[����\����
struct LoadAssetsData {
    // �R���X�g���N�^
    // @ Arg1 : �ǂݍ��݃t�@�C����
    // @ Arg2 : �ǂݍ��݌�
    // @ Arg3 : �ǂݍ��ݎ��̃��f���̑傫���i�f�t�H���g�F1�j
    // @ Arg4 : �ǂݍ��ݎ����]�����邩�i�f�t�H���g�Ffalse�j
    LoadAssetsData(const std::string& file, const unsigned int count, const float scale = 1.f, const bool flip = false) 
        : name(file)
        , count(count) 
        , scale(scale)
        , flip(flip) {
    }

    std::string name;  // �ǂݍ��݃t�@�C����
    int         count; // �ǂݍ��݌�
    float       scale; // �ǂݍ��ݎ��̃��f���̑傫��
    bool        flip;  // �ǂݍ��ݎ����]�����邩
};


using LoadAssetsList = std::vector<LoadAssetsData>;


// �w��t�@�C����ǂݍ���
// @ Arg1 : �ǂݍ��݃t�@�C�����
void LoadFile(const LoadAssetsData& data) {
    //----- �X���b�h���ύX
    SetThreadDescription(GetCurrentThread(), L"AssetsLoadThread");

    //----- COM�I�u�W�F�N�g�̏�����
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    //----- �ǂݍ���
    for (int i = 0; i < data.count; i++) {
        auto release = FileStorage::Get()->LoadModel(data.name, data.scale, data.flip);
        FileStorage::Get()->ReturnModel(release);
    }
}


// ���X�g�Ŏw�肵�����̂�S�ēǂݍ���
void AllLoadFile(LoadAssetsList* list) {
    //----- �ϐ��錾
    std::vector<std::thread> threadList;    // �ǂݍ��ݗp�X���b�h�̓��I�z��

    //----- �ǂݍ��݃��[�v
    for (auto& it : *list) {
        //----- �ǂݍ���
        while (it.count > 0) {  // �ǂݍ��ݐ����Ȃ��Ȃ�i���S�ēǂݍ��݂��J�n�����j�܂œǂݍ���
            //----- �ǂݍ��ݐ��̐ݒ�
            unsigned int loadFileCount = LOAD_ASSETS_SPRITE_COUNT;
            loadFileCount = ((it.count -= loadFileCount) < 0 ? LOAD_ASSETS_SPRITE_COUNT + it.count : LOAD_ASSETS_SPRITE_COUNT);// �ǂݍ��݂����iit.count��0�ȉ��j�̏ꍇ�͂��̕��␳����

            //----- �ǂݍ��݂̊J�n
            LoadAssetsData data(it.name,loadFileCount,it.scale,it.flip);
            threadList.push_back(std::thread(LoadFile, data));  // �ǂݍ��݊J�n
        }
    }

    //----- �S�ẴX���b�h�ǂݍ��݂��I������܂őҋ@
    for (auto& it : threadList) {
        if (it.joinable()) {
            it.join();
        }
    }
}


// ���f���Ȃǂ��s���ēǂݍ���
void FirstLoad(void) {
    //----- �ϐ��錾
    LoadAssetsList list;

    //----- �ǂݍ��݃��f���̒ǉ�
    list.push_back(LoadAssetsData(LOAD_BLOCK_FILENAME    , 1, LOAD_BLOCK_SCALE));
    list.push_back(LoadAssetsData(LOAD_OBSTACLES_FILENAME, 1, LOAD_OBSTACLES_SCALE));
    list.push_back(LoadAssetsData(LOAD_PLAYER_FILENAME   , 1, LOAD_PLAYER_SCALE));

    //----- �ǂݍ���
    AllLoadFile(&list);
}
