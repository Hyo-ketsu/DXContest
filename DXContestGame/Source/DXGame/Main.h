#ifndef __MAIN_H__
#define __MAIN_H__

//--- �v���g�^�C�v�錾
unsigned int GetAppWidth();
unsigned int GetAppHeight();

void Init();
void Uninit();
void Update(float deltaTime);
void Draw();

// �x���i�K�j�����W�A���ɕϊ����鎮
const float GetRad(const float rad);

#endif // __MAIN_H__