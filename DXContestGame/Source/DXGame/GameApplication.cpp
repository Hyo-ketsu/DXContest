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
    //----- マウス座標を格納する
    m_mouseTrasform = in; 

    //----- ウィンドウサイズを超えたマウス座標を補正する
    if (m_mouseTrasform.x > m_windowSizeX) m_mouseTrasform.x = m_windowSizeX;
    if (m_mouseTrasform.y > m_windowSizeY) m_mouseTrasform.y = m_windowSizeY;
}