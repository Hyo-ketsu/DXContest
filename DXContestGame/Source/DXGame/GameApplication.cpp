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


// �}�E�X�J�[�\�����W�Z�b�^�[
void GameApplication::SetMouseTransform(const DirectX::XMINT2& in) {
    //----- �}�E�X���W���i�[����
    m_mouseTrasform = in; 

    //----- �E�B���h�E�T�C�Y�𒴂����}�E�X���W��␳����
    if (m_mouseTrasform.x > m_windowSizeX) m_mouseTrasform.x = m_windowSizeX;
    if (m_mouseTrasform.y > m_windowSizeY) m_mouseTrasform.y = m_windowSizeY;
}