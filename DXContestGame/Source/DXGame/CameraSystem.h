#ifndef ____CAMERASYSTEM_H____
#define ____CAMERASYSTEM_H____

#include <DXGame/Singleton.h>
#include <DXGame/CameraBase.h>


// カメラを保持等を行うクラス
class CameraSystem : public Singleton<CameraSystem> {
public:
    // デストラクタ
    ~CameraSystem(void) override {}


    // カメラを登録する
    // @ Arg1 : 追加するカメラコンポーネント
    void AddCamera(CameraBase* camera);
    // カメラの登録を削除する
    // @ Arg1 : 削除するカメラコンポーネント
    void DeleteCamera(CameraBase* camera);


    // カメラを取得する
    // @ Memo : メインカメラ、メインが設定されていなければ登録されたのが速いカメラを返却する
    // @ Memo : カメラが一つも存在しなければ例外を投げます
    // @ Ret  : 現在のカメラ
    CameraBase const* GetCamera(void) const;

private:
    // コンストラクタ
    CameraSystem(void) {}

    // フレンド宣言
    friend class Singleton<CameraSystem>;

    std::vector<CameraBase*> m_camera;  // カメラ情報を保持する
};


#endif // !____CAMERASYSTEM_H____
