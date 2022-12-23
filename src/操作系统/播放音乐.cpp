#ifdef _WIN32
#include<vector>
#include<string>
#include<windows.h>
using namespace std;
#pragma comment(lib,"winmm.lib") 


KrnlnApi BOOL  播放音乐(const vector<unsigned char>& 欲播放的音乐, bool 是否循环播放, bool 是否同步播放) {
	return  ::PlaySoundW(wstring((wchar_t*)欲播放的音乐.data(), 欲播放的音乐.size()).c_str(), 0, (SND_MEMORY | (是否循环播放 ? SND_LOOP : 0) | (是否同步播放 ? SND_SYNC : SND_ASYNC)));
}
KrnlnApi BOOL  播放音乐(const wstring& 欲播放的音乐, bool 是否循环播放, bool 是否同步播放) {


	return ::PlaySoundW(欲播放的音乐.c_str(), 0, (SND_FILENAME | (是否循环播放 ? SND_LOOP : 0) | (是否同步播放 ? SND_SYNC : SND_ASYNC)));
}
KrnlnApi BOOL 播放音乐(const string& 欲播放的音乐, bool 是否循环播放, bool 是否同步播放) {
	return ::PlaySoundA(欲播放的音乐.c_str(), 0, (SND_FILENAME | (是否循环播放 ? SND_LOOP : 0) | (是否同步播放 ? SND_SYNC : SND_ASYNC)));
}
KrnlnApi  BOOL  停止播放() {
	return PlaySound(NULL, NULL, SND_PURGE);
}
#endif