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
    ~SceneLoader(void) override;


    // 現在シーンを取得する
    SceneBase* const GetScene(void) const;


    // シーンを移動する
    // @ Temp : 移動したいシーン
    template <typename MoveScene>
    void MoveScene(void);
    // シーンを削除する
    // @ Memo : 全てのシーンを削除します
    void DeleteScene(void);


    // 更新処理を行う
    void Update(void);
    // 描画処理を行う
    void Draw(void);

private:
    // コンストラクタ
    SceneLoader(void);


    // フレンド宣言
    friend class Singleton<SceneLoader>;

    std::unique_ptr<SceneBase> m_scene;     // 現在のシーン
    std::unique_ptr<SceneBase> m_newScene;  // 新しいシーン
};


// シーンを移動する
// @ Temp : 移動したいシーン
template <typename MoveScene>
void SceneLoader::MoveScene(void) {
    //----- アソート
    static_assert(std::is_base_of_v<SceneBase, MoveScene>, "Template error! Not a class that inherits SceneBase!");    // シーンから継承されているかのアソート

    //----- 移動
    m_newScene = std::make_unique<MoveScene>();
    m_newScene->InitScene();
}


#endif // !____SCENELOADER_H____
