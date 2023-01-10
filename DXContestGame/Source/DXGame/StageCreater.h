#ifndef ____STAGECREATER_H___
#define ____STAGECREATER_H___

#include <DXGame/GameObject.h>
#include <DXGame/Obstacles.h>
#include <list>


class StageCreaterControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;

    // 障害物を生成する
    void CreateObstacles(void);

private:
    std::vector<GameObject*> m_block;       // ブロックへのアクセスを保持
    std::vector<Obstacles*>  m_obstacles;   // 障害物へのアクセスを保持
    float                    m_moveSpeed;   // プレイヤーがどれだけ移動しているか
    unsigned int             m_moveCount;   // ブロックの移動処理のカウンター
    unsigned int             m_lastIndex;   // 最後に後ろに移動したブロックのインデックス
    int                      m_obstaclesFlame;      // 障害物の生成間隔
    Transform                m_firstPlayerTrans;    // プレイヤーの初期位置
};


class StageCreater : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____STAGECREATER_H___
