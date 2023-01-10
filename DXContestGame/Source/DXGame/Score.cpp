#include <DXGame/Score.h>
#include <DXGame/Number.h>
#include <DXGame/GameDefine.h>


void Score::Prefab(void) {
    //----- ステータス設定
    SetName(NAME_SCORE);

    //----- コンポーネントの追加
    AddComponent<NumberShow>();
}
