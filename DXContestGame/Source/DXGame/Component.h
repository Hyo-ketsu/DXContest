#ifndef ____COMPONENT_H____
#define ____COMPONENT_H____

#include <DXGame/ClassName.h>


class Component {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    Component(GameObject* gameObject);
    // デストラクタ
    virtual ~Component(void) {}


    // アクティブゲッター
    const bool GetActive(void) const { return m_isActive; }
    // アクティブセッター
    void SetActive(const bool in) { m_isActive = in; }


    // 初期化可否ゲッター
    const bool GetInit(void) const { return m_isInit; }


    // 所属ゲームオブジェクトゲッター
    const GameObject* GetGameObject(void) const { return m_gameObject; }


    // 初期化処理
    virtual void Start(void) = 0;
    // 更新処理
    virtual void Update(void) {}
    // 後更新処理
    virtual void LateUpdate(void) {}
    // 描画処理
    virtual void Draw(void) {}

protected:
    bool        m_isActive;     // 現在有効か
    bool        m_isInit;       // 初期化はされているか
    GameObject* m_gameObject;   // このコンポーネントが所属しているゲームオブジェクト
};


#endif // !____COMPONENT_H____
