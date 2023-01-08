#ifndef ____HP_H____
#define ____HP_H____

#include <DXGame/Component.h>


// HPコンポーネント
class HP : public Component {
public:
    using Component::Component;

    void Start(void) override {}


    // 体力ゲッター
    const int GetHP(void) const { return m_hp; }
    // 体力セッター
    void SetHP(const int in) { m_hp = in; }


    // ダメージを与える
    // @ Arg1 : ダメージ値（負値で回復）
    void Damage(const int damage);


    // 生死判定
    // @ Ret  : 死んでいるか
    const bool IsDead(void) const;


private:
    int m_hp = 1;
};


#endif // !____HP_H____
