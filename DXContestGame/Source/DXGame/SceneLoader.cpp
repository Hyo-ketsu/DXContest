#include <DXGame/SceneLoader.h>
#include <DXGame/DirectX.h>


// デストラクタ
SceneLoader::~SceneLoader(void) {
    DeleteScene();
}
// コンストラクタ
SceneLoader::SceneLoader(void)
    : m_scene(nullptr) 
    , m_newScene(nullptr) {
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
    //----- 新しいシーンがあればそれを追加する
    if (m_newScene != nullptr) m_scene = std::move(m_newScene);

    //----- 更新処理を行う
    if (m_scene != nullptr) m_scene->GetUpdater()->Update();
}
// 描画処理を行う
void SceneLoader::Draw(void) {
    //----- 前描画処理
    BeginDrawDX();

    //----- 描画処理
    if (m_scene != nullptr) m_scene->GetUpdater()->Draw();

    //----- 後描画処理
    EndDrawDX();
}