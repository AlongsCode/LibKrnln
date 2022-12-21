#include <ctime>


KrnlnApi int 取某月天数(int 年份, int 月份) {
	std::tm time_in = { 0 };
	time_in.tm_year = 年份 - 1900;
	time_in.tm_mon = 月份 - 1;
	// 使用 mktime 计算日期是否有效，从而确定月份的天数
	if (std::mktime(&time_in) == -1) {
		return 0;
	}
	return time_in.tm_mday;
}


