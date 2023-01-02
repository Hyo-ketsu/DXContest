#ifndef ____SCENELOADER_H____
#define ____SCENELOADER_H____

#include <DXGame/Singleton.h>
#include <DXGame/ClassName.h>
#include <DXGame/GameObjectUpdater.h>
#include <DXGame/Scene.h>


// シーンを管理するクラス
class SceneLoader : public Singleton<SceneLoader> {
public:
    // デストラクタ
    ~SceneLoader(void);


    // シーンを移動する
    // @ Temp : 移動したいシーン
    template <typename MoveScene>
    void MoveScene(void);


    // 現在シーンを取得する
    SceneBase* GetScene(void);


    // ゲームアップデーター初期化
    void InitGameUpdater(void);
    // ゲームアップデーター終了
    void UninitGameUpdater(void);


    // ゲームアップデーターを取得する
    // @ Memo : 未初期化時、例外を投げます
    // @ Ret  : ゲームアップデーターへの参照
    GameUpdater& GetGameUpdaterRef(void);

private:
    // コンストラクタ
    SceneLoader(void);


    // フレンド宣言
    friend class Singleton<SceneLoader>;


    std::unique_ptr<GameUpdater> m_gameUpdater;     // ゲームアップデーター
    std::unique_ptr<SceneBase>   m_currentScene;    // 現在のシーン
};


// シーンを移動する
// @ Temp : 移動したいシーン
template <typename MoveScene>
void SceneLoader::MoveScene(void) {
    //----- アソート
    static_assert(std::is_same_v<SceneBase, T>, "Template error! Not a class that inherits SceneBase!");    // シーンから継承されているかのアソート

    //----- 移動
    m_currentScene = std::make_unique<MoveScene>();
}


#endif // !____SCENELOADER_H____
