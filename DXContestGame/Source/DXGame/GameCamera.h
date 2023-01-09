#ifndef ____GAMECAMERA_H____
#define  ____GAMECAMERA_H____

#include <DXGame/CameraBase.h>
#include <DXGame/GameObject.h>
#include <DXGame/Player.h>


class GameCameraCamera : public CameraBase {
public:
    using CameraBase::CameraBase;
    void Start(void) override;
    void Update(void) override;
};


// プレイヤー追従カメラ
class GameCamera : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____GAMECAMERA_H____
