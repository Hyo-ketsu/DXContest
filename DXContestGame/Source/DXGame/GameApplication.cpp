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
    //----- �E�B���h�E�T�C�Y�𒴂����}�E�X���W�𖳎�����
    bool isX = in.x <= m_windowSizeX;
    bool isY = in.y <= m_windowSizeY;

    //----- �}�E�X���W���i�[����
    m_mouseTrasform.x = isX ? in.x : m_mouseTrasform.x;
    m_mouseTrasform.y = isY ? in.y : m_mouseTrasform.y;
}