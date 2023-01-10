#ifndef ____SCORE_H____
#define ____SCORE_H____

#include <DXGame/GameObject.h>
#include <DXGame/Component.h>
#include <DXGame/Number.h>


class ScoreControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;

private:
    DirectX::XMFLOAT3 m_firstPos;   // プレイヤーの初期位置
    NumberShow* m_number;           // 番号表示コンポーネント保持
};


class Score : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____SCORE_H____
