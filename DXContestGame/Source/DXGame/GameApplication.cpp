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
