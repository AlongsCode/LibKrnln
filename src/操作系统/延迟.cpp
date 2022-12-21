#ifdef _WIN32
#include <windows.h>

KrnlnApi BOOL 延迟(INT64 millisecond) {
	LARGE_INTEGER liDueTime = { 0 };
	liDueTime.QuadPart = -10 * millisecond * 1000 * 1;
	HANDLE hTimer = NULL;
	hTimer = ::CreateWaitableTimerW(0, FALSE, 0);
	if (NULL == hTimer)
		return FALSE;
	SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0);
	while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, 1, QS_TIMER) != WAIT_OBJECT_0) {
		MSG msg;
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) { //处理事件
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	CloseHandle(hTimer);
	return TRUE;
}
#endif
