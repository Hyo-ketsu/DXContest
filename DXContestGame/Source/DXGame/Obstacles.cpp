#include <DXGame/Obstacles.h>
#include <DXGame/Collsion.h>
#include <DXGame/ModelComponent.h>
#include <DXGame/GameDefine.h>


void Obstacles::Prefab(void) {
    //----- 当たり判定の追加
    auto collsion = AddCollsion(false, DirectX::XMFLOAT3(2.5f, 2.5f, 2.5f));
    collsion->SetTag(Tag::Ground);

    //----- コンポーネントの追加
    ModelComponent* model = new ModelComponent(this, LOAD_OBSTACLES_FILENAME, LOAD_OBSTACLES_SCALE);
    AddComponent(model);
}
