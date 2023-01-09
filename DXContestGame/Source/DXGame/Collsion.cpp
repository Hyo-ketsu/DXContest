#include <DXGame/Collsion.h>
#include <DXGame/CollsionSystem.h>
#include <DXGame/GameObject.h>
#include <float.h>
#include <array>


// �ǂ��̖ʂ�
enum HitCollsionDirection {
    X = 0,
    Y,
    Z,
};


// �R���X�g���N�^
Collsion::Collsion(GameObject* gameObject, const bool isHitMove, const DirectX::XMFLOAT3& size, const DirectX::XMFLOAT3& pos)
    : m_tag(Tag::Non)
    , m_isActive(true)
    , m_isHitMove(isHitMove)
    , m_gameObject(gameObject)
    , m_pos(pos)
    , m_size(size) {
    CollsionSystem::Get()->AddCollsion(this);
}
// �f�X�g���N�^
Collsion::~Collsion(void) {
    CollsionSystem::Get()->DeleteCollsion(this);
}


// �^����ꂽ�����蔻��ƏՓ˔�����s��
void Collsion::CollsionHitCheck(Collsion* const collsion) {
    //----- �Փ˔�����s��������
    if (this->GetActive()    == false)  return;
    if (collsion->GetActive() == false) return;
    if (this->GetGameObject()->GetActive()    == false)  return;
    if (collsion->GetGameObject()->GetActive() == false) return;
    if (this == collsion)                                return;
    if (this->GetTag() == collsion->GetTag())            return;

    //----- �ϐ��錾
    DirectX::XMFLOAT3 thisTransform;    // ���g�̍��W
    DirectX::XMFLOAT3 targetTransform;  // �Փˑ���̍��W
    std::array<bool,3> hitDirection; // ��������������\��
    hitDirection.fill(false);

    //----- ������
    thisTransform.x = m_pos.x + m_gameObject->GetTransform().pos.x;
    thisTransform.y = m_pos.y + m_gameObject->GetTransform().pos.y;
    thisTransform.z = m_pos.z + m_gameObject->GetTransform().pos.z;
    targetTransform.x = collsion->m_pos.x + collsion->GetGameObject()->GetTransform().pos.x;
    targetTransform.y = collsion->m_pos.y + collsion->GetGameObject()->GetTransform().pos.y;
    targetTransform.z = collsion->m_pos.z + collsion->GetGameObject()->GetTransform().pos.z;

    //----- ����
    //----- �Ώ� +X �ʔ���
    if (thisTransform.x - m_size.x / 2 < targetTransform.x + collsion->m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x + collsion->m_size.x / 2)
    {
        hitDirection.at(HitCollsionDirection::X) = true;
    }
    //----- �Ώ� -X �ʔ���
    if (thisTransform.x - m_size.x / 2 < targetTransform.x - collsion->m_size.x / 2 &&
        thisTransform.x + m_size.x / 2 > targetTransform.x - collsion->m_size.x / 2)
    {
        hitDirection.at(HitCollsionDirection::X) = true;
    }
    //----- �Ώ� +Y �ʔ���
    if (thisTransform.y - m_size.y / 2 < targetTransform.y + collsion->m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y + collsion->m_size.y / 2)
    {
        hitDirection.at(HitCollsionDirection::Y) = true;
    }
    //----- �Ώ� -Y �ʔ���
    if (thisTransform.y - m_size.y / 2 < targetTransform.y - collsion->m_size.y / 2 &&
        thisTransform.y + m_size.y / 2 > targetTransform.y - collsion->m_size.y / 2)
    {
        hitDirection.at(HitCollsionDirection::Y) = true;
    }
    //----- �Ώ� +Z �ʔ���
    if (thisTransform.z - m_size.z / 2 < targetTransform.z + collsion->m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z + collsion->m_size.z / 2)
    {
        hitDirection.at(HitCollsionDirection::Z) = true;
    }
    //----- �Ώ� -Z �ʔ���
    if (thisTransform.z - m_size.z / 2 < targetTransform.z - collsion->m_size.z / 2 &&
        thisTransform.z + m_size.z / 2 > targetTransform.z - collsion->m_size.z / 2)
    {
        hitDirection.at(HitCollsionDirection::Z) = true;
    }

    //----- ����ԋp
    if (hitDirection.at(HitCollsionDirection::X) && hitDirection.at(HitCollsionDirection::Y) && hitDirection.at(HitCollsionDirection::Z)) {
        //----- �Փ˂��Ă���B�Փˏ���ǉ�
        auto data = m_gameObject->GetCollsionData();
        auto coll = CollsionHitData();
        coll.hitCollsion = collsion;
        data.list.push_back(coll);
        m_gameObject->SetCollsionData(data);
    }
    else {
        //----- �Փ˂��Ă��Ȃ��B���̂܂܏I��
        return;
    }

    ////----- �����߂��p�ϐ��錾
    //float thisRemove = 0.0f;    // �����߂����i�j
    //float targetRemove = 0.0f;  // �����߂����i�j

    ////----- �����߂����ݒ�
    //if (m_isHitMove && collsion.m_isHitMove) {
    //    //----- �ǂ���Ƃ������߂����s��
    //    thisRemove = 0.5f;
    //    targetRemove = 0.5f;
    //}
    //else {
    //    if (m_isHitMove) {
    //        //----- ���g�͈����߂����s��
    //        thisRemove = 1.0f;
    //        targetRemove = 0.0f;
    //    }
    //    if (collsion.m_isHitMove) {
    //        //----- �Ώۂ͈����߂����s��
    //        thisRemove = 0.0f;
    //        targetRemove = 1.0f;
    //    }
    //}
}
