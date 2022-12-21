#if defined(_WIN32)
#include<windows.h>
#else
#include <cstdlib>
#endif
KrnlnApi int 取屏幕高度() {
#if defined(_WIN32)
	return GetSystemMetrics(SM_CYSCREEN);
#elif defined(__linux__)
	const char* heightStr = std::getenv("DISPLAY_HEIGHT");
	if (heightStr) {
		return std::atoi(heightStr);
	}
	else {
		// 如果获取失败，则返回0
		return 0;
	}
#else
	// 其他系统
#endif
}
