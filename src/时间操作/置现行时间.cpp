#include <chrono>
#include <ctime>

#ifdef _WIN32
#include<windows.h>
#else
#include <time.h>
#endif // _WIN32



KrnlnApi bool 置现行时间(const std::tm& tm)
{

#ifdef _WIN32
	SYSTEMTIME now = { 0 };
	now.wYear = tm.tm_year + 1900;
	now.wMonth = tm.tm_mon + 1;
	now.wDay = tm.tm_mday;
	now.wHour = tm.tm_hour;
	now.wMinute = tm.tm_min;
	now.wSecond = tm.tm_sec;
	now.wMilliseconds = 0;
	return SetLocalTime(&now);
#else
	std::time_t time = std::mktime(const_cast<std::tm*>(&tm));

	if (time == -1) {
		// mktime failed
		return false;
	}
	std::time_t result = stime(&time);
	if (result == -1) {
		// stime failed
		return false;
	}

	return true;
#endif // _WIN32

}
