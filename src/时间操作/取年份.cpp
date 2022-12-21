#include <ctime>



KrnlnApi int 取年份(const std::tm& 时间) {
	return 时间.tm_year + 1900;
}