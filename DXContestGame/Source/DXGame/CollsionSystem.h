#ifndef ____COLLSIONSYSTEM_H____
#define ____COLLSIONSYSTEM_H____

#include <DXGame/Singleton.h>
#include <DXGame/Collsion.h>


// 衝突判定を行うクラス
class CollsionSystem : public Singleton<CollsionSystem> {
public:
    // デストラクタ
    ~CollsionSystem(void) override {}


    // 当たり判定の追加
    // @ Arg1 : 追加する当たり判定
    void AddCollsion(Collsion* collsion);
    // 当たり判定の削除
    // @ Arg1 : 削除する当たり判定
    void DeleteCollsion(Collsion* collsion);


    // 全ての当たり判定を判定する
    void AllCollsionHit(void);
private:
    // コンストラクタ
    CollsionSystem(void) {}


    // friendクラス宣言
    friend class Singleton<CollsionSystem>;

    std::vector<Collsion*> m_collsion;  // 当たり判定の保持
};


#endif // !____COLLSIONSYSTEM_H____
