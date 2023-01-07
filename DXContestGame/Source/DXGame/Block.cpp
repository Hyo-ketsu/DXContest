#include <DXGame/Block.h>
#include <DXGame/ModelComponent.h>


void Block::Prefab(void) {
    ModelComponent* model = new ModelComponent(this, "Hoge.ply", 1);
    AddComponent(model);
}
