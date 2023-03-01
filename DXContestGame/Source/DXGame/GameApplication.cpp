#include <DXGame/GameApplication.h>


// デストラクタ
GameApplication::~GameApplication(void) {
}
// コンストラクタ
GameApplication::GameApplication(void) 
    : m_isGameEnd(false)
    , m_windowSizeX(0) 
    , m_windowSizeY(0)
    , m_mouseTrasform({ 0,0 }) {
}


// マウスカーソル座標セッター
void GameApplication::SetMouseTransform(const DirectX::XMINT2& in) {
    //----- ウィンドウサイズを超えたマウス座標を無視する
    bool isX = in.x <= m_windowSizeX;
    bool isY = in.y <= m_windowSizeY;

    //----- マウス座標を格納する
    m_mouseTrasform.x = isX ? in.x : m_mouseTrasform.x;
    m_mouseTrasform.y = isY ? in.y : m_mouseTrasform.y;
}