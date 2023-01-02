#ifndef ____SCENE_H____
#define ____SCENE_H____


// シーンを作る際の抽象クラス
class SceneBase {
public:
    // シーンを生成する
    virtual void InitScene(void) = 0;
};


#endif // !____SCENE_H____
