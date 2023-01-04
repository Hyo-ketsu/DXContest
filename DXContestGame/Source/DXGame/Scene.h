#ifndef ____SCENE_H____
#define ____SCENE_H____

#include <DXGame/ClassName.h>


// シーンを作る際の抽象クラス
class SceneBase {
public:
    // コンストラクタ
    SceneBase(void);
    // デストラクタ
    ~SceneBase(void);


    // シーンを生成する
    virtual void InitScene(void) = 0;


    // ゲームアップデーターゲッター
    GameUpdater *const GetUpdater(void) const { return m_updater.get(); }

private:
    std::unique_ptr<GameUpdater> m_updater; // ゲームアップデーター
};


#endif // !____SCENE_H____
