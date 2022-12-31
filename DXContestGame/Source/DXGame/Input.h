#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>


// �L�[���͏���������
// @ Ret  : �������ɐ���������
const HRESULT InitInput(void);
// �L�[���͏I������
void UninitInput(void);


// �L�[���͏����擾����
void UpdateInput(void);


// �w�肵���L�[�����͂��ꂽ��
// @ Ret  : ���͂���Ă��邩
// @ Arg1 : ���̓L�[
bool IsKeyPress(const BYTE key);
// �w�肵���L�[�������ꂽ��
// @ Ret  : ���͂���Ă��邩
// @ Arg1 : ���̓L�[
bool IsKeyTrigger(const BYTE key);
// �w�肵���L�[�������ꂽ��
// @ Ret  : ���͂���Ă��邩
// @ Arg1 : ���̓L�[
bool IsKeyRelease(const BYTE key);

#endif // __INPUT_H__