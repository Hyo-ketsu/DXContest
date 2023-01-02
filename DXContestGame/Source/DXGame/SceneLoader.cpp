#include <DXGame/SceneLoader.h>


// デストラクタ
SceneLoader::~SceneLoader(void) {
    UninitGameUpdater();
}


// コンストラクタ
SceneLoader::SceneLoader(void)
    : m_gameUpdater(nullptr)
    , m_currentScene(nullptr) {
    InitGameUpdater();
}


// 現在シーンを取得する
SceneBase* SceneLoader::GetScene(void) {
    return m_currentScene ? m_currentScene.get() : nullptr; // 現在のシーンが設定されていればそれのポインタ、そうでなければ nullptr
}


// ゲームアップデーター初期化
void SceneLoader::InitGameUpdater(void) {
    m_gameUpdater = std::make_unique<std::remove_reference<decltype(*m_gameUpdater.get())>::type>();
}
// ゲームアップデーター終了
void SceneLoader::UninitGameUpdater(void) {
    m_gameUpdater.reset();
}


// ゲームアップデーターを取得する
GameUpdater& SceneLoader::GetGameUpdaterRef(void) {
    if (m_gameUpdater) {
        //----- 存在する。そのまま返却
        return *m_gameUpdater.get();
    }
    else {
        //----- 存在しない。例外を投げる
        throw std::logic_error("Exception! Value 'm_gameUpdater' not initialized");
    }
}
