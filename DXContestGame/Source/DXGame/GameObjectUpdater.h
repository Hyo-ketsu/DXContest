#ifndef ____GAMEOBJECTUPDATER_H____
#define ____GAMEOBJECTUPDATER_H____

#include <DXGame/ClassName.h>
#include <DXGame/GameObject.h>


class GameUpdater {
public:
    // コンストラクタ
    GameUpdater(void);
    // デストラクタ
    ~GameUpdater(void);


    // 更新処理を行う
    void Update(void);
    // 描画処理を行う
    void Draw(void);


    // ゲームオブジェクトを追加する
    // @ Arg1 : 追加するゲームオブジェクトのポインタ
    void AddGameObject(GameObject* gameObject);
    // ゲームオブジェクトを削除する
    // @ Ret  : 削除に成功したか
    // @ Arg1 : 削除するゲームオブジェクトのポインタ
    const bool DeleteGameObject(GameObject* gameObject);


    // ゲームオブジェクトを名前検索する
    // @ Memo : 単体で検索します。複数同名のオブジェクトが存在する場合はどれを返すかは保証しません
    // @ Ret  : 検索結果（なければ nullptr）
    // @ Arg1 : 検索名
    GameObject* FindGameObject(const std::string& name) const;


private:
    // 削除インデックスに登録されているゲームオブジェクトの消去
    void DeleteGameObject(void);


    std::vector<std::unique_ptr<GameObject>> m_gameObject;  // 保持しているゲームオブジェクト
    std::vector<unsigned int>                m_deleteIndex; // ゲームオブジェクトの削除インデックス
};


#endif // !____GAMEOBJECTUPDATER_H____
