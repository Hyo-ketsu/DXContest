#include <DXGame/Timer.h>
#include <DXGame/WinUtil.h>


std::unique_ptr<unsigned int> Timer::ms_globalTime; // �S�̎���


// �R���X�g���N�^
Timer::Timer(void) {
    m_time = *ms_globalTime.get();
}
// �f�X�g���N�^
Timer::~Timer(void) {

}


// ������
void Timer::InitTime(void) {
    //----- �����ݒ�
    if (!(ms_globalTime)) {
        timeBeginPeriod(1);
        ms_globalTime = std::make_unique<std::remove_reference<decltype(*ms_globalTime)>::type>(timeGetTime());
    }
}
// �X�V
void Timer::UpdateTime(void) {
    //----- �X�V
    *ms_globalTime.get() = timeGetTime();
}
// �I��
void Timer::UninitTime(void) {
    //----- �I��
    if (ms_globalTime) {
        timeEndPeriod(1);
        ms_globalTime.reset();
    }
}


// 60FPS����
const bool Timer::IsFpsCheck(void) {
    //----- ���ݎ��Ԏ擾
    unsigned int newTime = *ms_globalTime.get();

    //----- 60FPS�o�ߔ���
    if (newTime - m_fpsTime >= 1000 / 60) { // 1�b / 60�t���[���ȏ�o�߂��Ă��邩
        m_fpsTime = newTime;
        return true;
    }
    else {
        return false;
    }
}


// �O����s������̌o�ߎ���
const float Timer::DeltaTime(void) {
    //----- �ϐ��錾
    float ret;

    //----- �o�ߎ��Ԍv�Z
    if (m_time != 0) {
        ret = *ms_globalTime.get() - m_time;
    }
    else {
        ret = 0;
    }

    //----- ���Ԃ̍X�V
    m_time = *ms_globalTime.get();

    //----- �ԋp
    return ret / 1000;  // ms��b�ɕϊ�
}















//--- �O���[�o���ϐ�
Frame g_fps;
Time  g_deltaTime;
DWORD g_preExec;


void InitTimer(Frame fps) {
	SetFPS(fps);
	timeBeginPeriod(1);
	g_preExec = timeGetTime();
}
void UninitTimer() {
	timeEndPeriod(1);
}
bool UpdateTimer() {
	DWORD time = timeGetTime();
	DWORD diff = time - g_preExec;
	if (diff >= 1000 / 60)
	{
		g_deltaTime = diff / 1000.f;
		g_preExec = time;
		return true;
	}
	return false;
}

void SetFPS(Frame fps) {
	g_fps = fps;
}
Frame GetFPS() {
	return g_fps;
}


Time GetDeltaTime() {
	return g_deltaTime;
}

Time ConvertFrameToTime(Frame frame) {
	return static_cast<float>(frame) / g_fps;
}
Frame ConvertTimeToFrame(Time time) {
	return static_cast<Frame>(time * g_fps);
}