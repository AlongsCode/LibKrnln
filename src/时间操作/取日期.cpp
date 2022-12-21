#include <ctime>

KrnlnApi std::tm 取日期(std::tm 时间) {
	时间.tm_hour = 0;
	时间.tm_min = 0;
	时间.tm_sec = 0;
	return 时间;
}