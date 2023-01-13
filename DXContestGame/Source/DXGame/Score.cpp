#include <DXGame/Score.h>
#include <DXGame/Number.h>
#include <DXGame/GameDefine.h>
#include <DXGame/SceneLoader.h>
#include <DXGame/ScoreRecorder.h>


void ScoreControl::Start(void) {
    //----- �ϐ�������
    m_firstPos = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER)->GetTransform().pos;
    m_number = m_gameObject->GetComponent<NumberShow>();
    if (m_number == nullptr) throw std::exception("Errer! Non \"NumberShow\" Conponent!");
}
void ScoreControl::Update(void) {
    //----- �v���C���[���擾
    auto player = SceneLoader::Get()->GetScene()->GetUpdater()->FindGameObject(NAME_PLAYER);
    if (player == nullptr) return;

    //----- �����ʒu����̃v���C���[�̈ړ�����
    auto score = fabsf(m_firstPos.z - player->GetTransform().pos.z);
    m_number->SetNumber(score);

    //----- �X�R�A�̋L�^
    ScoreGlobalRecorder::Get()->SetScore(static_cast<unsigned int>(score));
}


void Score::Prefab(void) {
    //----- �X�e�[�^�X�ݒ�
    SetName(NAME_SCORE);

    //----- �R���|�[�l���g�̒ǉ�
    AddComponent<NumberShow>();
    AddComponent<ScoreControl>();
}
