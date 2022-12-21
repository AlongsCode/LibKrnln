#include <ctime>
KrnlnApi int 取秒(const std::tm& 时间) {
	return 时间.tm_sec;
}