#include <DXGame/Input.h>


BYTE g_keyTable[256];   // ���t���[���̃L�[����
BYTE g_oldTable[256];   // �O�t���[���̃L�[����


// �L�[���͏���������
const HRESULT InitInput() {
	//----- ��ԍŏ��̓��͂��擾
	GetKeyboardState(g_keyTable);
	return S_OK;
}
// �L�[���͏I������
void UninitInput(void) {
}


// �L�[���͏����擾����
void UpdateInput(void) {
	// �O�t���[�����͏����X�V
	memcpy_s(g_oldTable, sizeof(g_oldTable), g_keyTable, sizeof(g_keyTable));
	// ���t���[���̓��͂��擾
	GetKeyboardState(g_keyTable);
}


// �w�肵���L�[�����͂��ꂽ��
bool IsKeyPress(BYTE key) {
	return g_keyTable[key] & 0x80;
}
// �w�肵���L�[�������ꂽ��
bool IsKeyTrigger(BYTE key) {
	return (g_keyTable[key] ^ g_oldTable[key]) & g_keyTable[key] & 0x80;
}
// �w�肵���L�[�������ꂽ��
bool IsKeyRelease(BYTE key) {
	return (g_keyTable[key] ^ g_oldTable[key]) & g_oldTable[key] & 0x80;
}