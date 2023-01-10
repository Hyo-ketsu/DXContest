#include <DXGame/Block.h>
#include <DXGame/ModelComponent.h>


void Block::Prefab(void) {
    ModelComponent* model = new ModelComponent(this, "Block.obj", 0.2f);
    AddComponent(model);
}
