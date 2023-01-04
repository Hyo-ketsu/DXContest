#include <DXGame/SceneLoader.h>
#include <DXGame/DirectX.h>


// デストラクタ
SceneLoader::~SceneLoader(void) {
    DeleteScene();
}
// コンストラクタ
SceneLoader::SceneLoader(void)
    : m_scene(nullptr) {
}


// 現在シーンを取得する
SceneBase* const SceneLoader::GetScene(void) const {
    return m_scene ? m_scene.get() : nullptr; // 現在のシーンが設定されていればそれのポインタ、そうでなければ nullptr
}


// シーンを削除する
void SceneLoader::DeleteScene(void) {
    m_scene.reset();
}


// 更新処理を行う
void SceneLoader::Update(void) {
    m_scene->GetUpdater()->Update();
}
// 描画処理を行う
void SceneLoader::Draw(void) {
    //----- 前描画処理
    BeginDrawDX();

    //----- 描画処理
    m_scene->GetUpdater()->Draw();

    //----- 後描画処理
    EndDrawDX();
}