#include <DXGame/GameApplication.h>


// �f�X�g���N�^
GameApplication::~GameApplication(void) {
}
// �R���X�g���N�^
GameApplication::GameApplication(void) 
    : m_isGameEnd(false)
    , m_windowSizeX(0) 
    , m_windowSizeY(0)
    , m_mouseTrasform({ 0,0 }) {
}
