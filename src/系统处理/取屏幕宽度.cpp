#if defined(_WIN32)
#include<windows.h>
#else
#include <cstdlib>
#endif
KrnlnApi int 取屏幕宽度() {
#if defined(_WIN32)
	return GetSystemMetrics(SM_CXSCREEN);
#elif defined(__linux__)
	const char* widthStr = std::getenv("DISPLAY_WIDTH");
	if (widthStr) {
		return std::atoi(widthStr);
	}
	else {
		return 0;
	}
#else
	// Other operating systems
#endif
}
