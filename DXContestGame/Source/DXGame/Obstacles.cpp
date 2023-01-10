#include <DXGame/Obstacles.h>
#include <DXGame/Collsion.h>
#include <DXGame/ModelComponent.h>
#include <DXGame/GameDefine.h>


void Obstacles::Prefab(void) {
    //----- �����蔻��̒ǉ�
    auto collsion = AddCollsion(false, DirectX::XMFLOAT3(2, 2, 2));
    collsion->SetTag(Tag::Ground);

    //----- �R���|�[�l���g�̒ǉ�
    ModelComponent* model = new ModelComponent(this, "Obstacles.fbx", 1);
    AddComponent(model);
}