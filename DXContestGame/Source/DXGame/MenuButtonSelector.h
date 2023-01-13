#ifndef ____MENUBUTTONSELECTOR_H____
#define ____MENUBUTTONSELECTOR_H____

#include <DXGame/Component.h>
#include <DXGame/GameObject.h>


// MenuGameObject用のコンポーネント
class MenuGameObjectClient : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override {}


    // MenuGameObjectで選択された際に行うアクション
    virtual void Action(void) = 0;
};


// タイトルなどの複数選択できる場面のボタンをまとめるコンポーネント
class MenuGameObjectControl : public Component{
public:
    using Component::Component;


    void Start(void) override;
    void Update(void) override;


    // ゲームオブジェクトを追加する
    // @ Memo : 追加するゲームオブジェクトが MenuGameObjectClient を保持していなければ例外を投げます
    // @ Arg1 : ゲームオブジェクト
    void AddGameObject(GameObject *gameObject);

private:
    std::vector<GameObject*> m_children;        // メニューで選択するオブジェクト
    unsigned int             m_currentCursor;   // カーソル位置
};


// MenuGameObjectControlを保持しているゲームオブジェクト
class MenuGameObject : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____MENUBUTTONSELECTOR_H____
