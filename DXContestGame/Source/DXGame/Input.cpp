#include <DXGame/Input.h>


BYTE g_keyTable[256];   // 現フレームのキー入力
BYTE g_oldTable[256];   // 前フレームのキー入力


// キー入力初期化処理
const HRESULT InitInput() {
	//----- 一番最初の入力を取得
	GetKeyboardState(g_keyTable);
	return S_OK;
}
// キー入力終了処理
void UninitInput(void) {
}


// キー入力情報を取得する
void UpdateInput(void) {
	// 前フレーム入力情報を更新
	memcpy_s(g_oldTable, sizeof(g_oldTable), g_keyTable, sizeof(g_keyTable));
	// 現フレームの入力を取得
	GetKeyboardState(g_keyTable);
}


// 指定したキーが入力されたか
bool IsKeyPress(BYTE key) {
	return g_keyTable[key] & 0x80;
}
// 指定したキーが押されたか
bool IsKeyTrigger(BYTE key) {
	return (g_keyTable[key] ^ g_oldTable[key]) & g_keyTable[key] & 0x80;
}
// 指定したキーが離されたか
bool IsKeyRelease(BYTE key) {
	return (g_keyTable[key] ^ g_oldTable[key]) & g_oldTable[key] & 0x80;
}