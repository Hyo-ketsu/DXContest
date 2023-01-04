#ifndef ____CAMERABASE_H____
#define ____CAMERABASE_H____

#include <DXGame/ClassName.h>
#include <DXGame/Component.h>


// カメラコンポーネント
class CameraBase : public Component {
public:
    // コンストラクタ
    // @ Arg1 : 所属ゲームオブジェクト
    // @ Arg2 : メインカメラに設定するか（デフォルト：false）
    CameraBase(GameObject* gameObject, const bool isMainCamera = false);
    // デストラクタ
    virtual ~CameraBase(void) override;


    // メインカメラゲッター
    const bool GetMainCamera(void) const { return m_isMainCamera; }
    // メインカメラセッター
    void SetMainCamera(const bool in) { m_isMainCamera = in; }


    // 注視点ゲッター
    DirectX::XMFLOAT3 GetLook(void) const { return m_look; }


    // ビュー行列の取得
    // @ Ret  : ビュー行列
    const DirectX::XMFLOAT4X4 GetViewMatrix(void) const;
    // プロジェクション行列の取得
    // @ Ret  : プロジェクション行列
    const DirectX::XMFLOAT4X4 GetProjectionMatrix(void) const;

protected:
    bool              m_isMainCamera;   // メインカメラとして設定されているか
    DirectX::XMFLOAT3 m_look;   // 注視点
    DirectX::XMFLOAT3 m_up;     // 
    float             m_fovy;   // 視野角
    float             m_aspect; // 画面比率
    float             m_near;   // 最短描画距離
    float             m_far;    // 最長描画距離
};


#endif // !____CAMERABASE_H____
