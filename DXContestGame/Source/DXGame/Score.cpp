#include <DXGame/Score.h>
#include <DXGame/Number.h>
#include <DXGame/GameDefine.h>


void Score::Prefab(void) {
    //----- �X�e�[�^�X�ݒ�
    SetName(NAME_SCORE);

    //----- �R���|�[�l���g�̒ǉ�
    AddComponent<NumberShow>();
}
