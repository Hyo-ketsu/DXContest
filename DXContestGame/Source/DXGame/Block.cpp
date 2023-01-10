#include <DXGame/Block.h>
#include <DXGame/GameDefine.h>
#include <DXGame/ModelComponent.h>


void Block::Prefab(void) {
    ModelComponent* model = new ModelComponent(this, LOAD_BLOCK_FILENAME, LOAD_BLOCK_SCALE);
    AddComponent(model);
}
