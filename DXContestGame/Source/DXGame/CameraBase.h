#ifndef ____CAMERABASE_H____
#define ____CAMERABASE_H____


// カメラの基礎となるクラス
class CameraBase {
public:
    // コンストラクタ
    CameraBase(void);

    // デストラクタ
    virtual ~CameraBase(void) {}
    virtual void Update(void) = 0;

    // ビュー行列の取得
    DirectX::XMFLOAT4X4 GetViewMatrix(void);

    // プロジェクション行列の取得
    DirectX::XMFLOAT4X4 GetProjectionMatrix(void);
    
    // 位置の取得
    DirectX::XMFLOAT3 GetPos(void) { return m_pos; }

    // 注視点の取得
    DirectX::XMFLOAT3 GetLook(void) { return m_look; }

protected:
    DirectX::XMFLOAT3 m_pos, m_look, m_up;  // ビュー行列の設定に必要な変数
    float m_fovy, m_aspect, m_near, m_far;  // プロジェクション行列の設定に必要な変数
};


#endif // !____CAMERABASE_H____
