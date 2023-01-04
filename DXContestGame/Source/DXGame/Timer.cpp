#include <DXGame/Timer.h>
#include <DXGame/WinUtil.h>


std::unique_ptr<unsigned int> Timer::ms_globalTime; // 全体時間


// コンストラクタ
Timer::Timer(void) {
    m_time = *ms_globalTime.get();
}
// デストラクタ
Timer::~Timer(void) {

}


// 初期化
void Timer::InitTime(void) {
    //----- 初期設定
    if (!(ms_globalTime)) {
        timeBeginPeriod(1);
        ms_globalTime = std::make_unique<std::remove_reference<decltype(*ms_globalTime)>::type>(timeGetTime());
    }
}
// 更新
void Timer::UpdateTime(void) {
    //----- 更新
    *ms_globalTime.get() = timeGetTime();
}
// 終了
void Timer::UninitTime(void) {
    //----- 終了
    if (ms_globalTime) {
        timeEndPeriod(1);
        ms_globalTime.reset();
    }
}


// 60FPS制御
const bool Timer::IsFpsCheck(void) {
    //----- 現在時間取得
    unsigned int newTime = *ms_globalTime.get();

    //----- 60FPS経過判定
    if (newTime - m_fpsTime >= 1000 / 60) { // 1秒 / 60フレーム以上経過しているか
        m_fpsTime = newTime;
        return true;
    }
    else {
        return false;
    }
}


// 前回実行時からの経過時間
const float Timer::DeltaTime(void) {
    //----- 変数宣言
    float ret;

    //----- 経過時間計算
    if (m_time != 0) {
        ret = *ms_globalTime.get() - m_time;
    }
    else {
        ret = 0;
    }

    //----- 時間の更新
    m_time = *ms_globalTime.get();

    //----- 返却
    return ret / 1000;  // msを秒に変換
}















//--- グローバル変数
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