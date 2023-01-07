#ifndef ____COLLSION_H____
#define ____COLLSION_H____

#include <DXGame/ClassName.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/Geometory.h>

    
// 当たり判定が衝突した際の情報を格納する
struct CollsionHitData {
    bool isProvFrameHit;    // 前フレームは当たっていたか
    Collsion* hitCollsion;  // 衝突対象の当たり判定
};


// CollsionHitDataの動的配列用
struct CollsionHitDataVector {
    // 情報を取得する
    // @ Arg1 : 全フレームに衝突した情報か
    std::vector<CollsionHitData> GetDate(const bool isProvFrameHit);


    std::vector<CollsionHitData> list;  // 衝突情報
};


// 当たり判定を行うクラス
// @ Memo : 四角形の当たり判定を行います
// @ Memo : 回転は考慮しません
class Collsion {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    // @ Arg2 : 引き戻しを行うか
    // @ Arg3 : 拡縮（デフォルト：全て1）
    // @ Arg4 : 相対座標（デフォルト：全て0）
    Collsion(GameObject* gameObject, const bool isHitMove, const DirectX::XMFLOAT3& size = DirectX::XMFLOAT3(1, 1, 1), const DirectX::XMFLOAT3& pos = DirectX::XMFLOAT3(0, 0, 0));
    // デストラクタ
    ~Collsion(void);


    // タグゲッター
    const Tag GetTag(void) const { return m_tag; }
    // タグセッター
    void SetTag(const Tag in) { m_tag = in; }


    // アクティブゲッター
    const bool GetActive(void) const { return m_isActive; }
    // アクティブゲッター
    void SetActive(const bool in) { m_isActive = in; }


    // 相対座標ゲッター
    const DirectX::XMFLOAT3 GetPos(void) const { return m_pos; }
    // 相対座標セッター
    void SetPos(const DirectX::XMFLOAT3& in) { m_size = in; }


    // 拡縮ゲッター
    const DirectX::XMFLOAT3 GetSize(void) const { return m_size; }
    // 拡縮セッター
    void SetSize(const DirectX::XMFLOAT3& in) { m_size = in; }


    // 所属ゲームオブジェクトゲッター
    GameObject* const GetGameObject(void) const { return m_gameObject; }


    // 与えられた当たり判定と衝突判定を行う
    // @ Memo : 衝突情報などは（衝突していれば）関数内で直接追加します
    // @ Arg1 : 対象の当たり判定
    void CollsionHitCheck(const Collsion& collsion);


private:
    Tag         m_tag;          // 自身に設定されたタグ
    bool        m_isActive;     // 有効か
    bool        m_isHitMove;    // 引き戻しは行うか
    GameObject* m_gameObject;   // 所属ゲームオブジェクト
    DirectX::XMFLOAT3 m_pos;    // 相対的座標
    DirectX::XMFLOAT3 m_size;   // 拡縮
};


//class Collision {
//public:
//    //----- 当たり判定を行う形状
//    struct Plane {
//        DirectX::XMFLOAT3 normal;
//        DirectX::XMFLOAT3 pos;
//    };
//
//    //----- 当たり判定を行う形状
//    struct Triangle {
//        DirectX::XMFLOAT3 p[3]; // 三角形の座標
//    };
//
//    struct Ray {
//        DirectX::XMFLOAT3 start;
//        DirectX::XMFLOAT3 direction;
//        float length;
//    };
//
//    //----- 当たり判定の結果
//    struct Result {
//        bool hit;
//        DirectX::XMFLOAT3 point;
//    };
//
//public:
//    //----- 形状ごとの当たり判定を実装
//    static Result CheckRayPlane(Ray ray, Plane plane);
//
//    //----- 形状ごとの当たり判定を実装
//    static Result CheckPointTraiangle(DirectX::XMFLOAT3 point, Triangle triangle);
//};


#endif // !____COLLSION_H____
