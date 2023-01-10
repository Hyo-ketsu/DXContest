#include <DXGame/Score.h>
#include <DXGame/Number.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneLoader.h>


void ScoreControl::Start(void) {
    //----- 変数初期化
    m_firstPos = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER)->GetTransform().pos;
    m_number = m_gameObject->GetComponent<NumberShow>();
    if (m_number == nullptr) throw std::exception("Errer! Non \"NumberShow\" Conponent!");
}
void ScoreControl::Update(void) {
    //----- プレイヤー情報取得
    auto player = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER);
    if (player == nullptr) return;

    //----- 初期位置からのプレイヤーの移動距離
    m_number->SetNumber(fabsf(m_firstPos.z - player->GetTransform().pos.z));
}


void Score::Prefab(void) {
    //----- ステータス設定
    SetName(NAME_SCORE);

    //----- コンポーネントの追加
    AddComponent<NumberShow>();
    AddComponent<ScoreControl>();
}
