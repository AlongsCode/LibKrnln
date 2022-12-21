#include <ctime>
KrnlnApi int 取分钟(const std::tm& 时间) {
	return 时间.tm_min;
}