#ifndef __TIMER_H__
#define __TIMER_H__

#include <DXGame/Singleton.h>


// �����Ŏ��Ԃ��Ǘ�����N���X
class Timer {
public:
    // �R���X�g���N�^
    Timer(void);
    // �f�X�g���N�^
    ~Timer(void);


    // ���ݎ��ԃQ�b�^�[
    const unsigned int& GetTime(void) const { return m_time; }


    // ������
    static void InitTime(void);
    // �X�V
    static void UpdateTime(void);
    // �I��
    static void UninitTime(void);


    // 60FPS����
    // @ Ret  : �X�V�\��
    const bool IsFpsCheck(void);


    // �O����s������̌o�ߎ���
    // @ Ret  : �o�ߎ���
    const float DeltaTime(void);

private:
    unsigned int m_time;    // ���ݎ���
    unsigned int m_fpsTime; // FPS�`�F�b�N�p
    static std::unique_ptr<unsigned int> ms_globalTime; // �S�̎���
};




//--- �^�錾
using Frame = unsigned short;
using Time  = float;

//--- �v���g�^�C�v�錾
void InitTimer(Frame fps);
void UninitTimer(void);
bool UpdateTimer(void);


void  SetFPS(Frame fps);
Frame GetFPS(void);


Time GetDeltaTime(void);


Time  ConvertFrameToTime(Frame frame);
Frame ConvertTimeToFrame(Time time);

#endif // __TIMER_H__