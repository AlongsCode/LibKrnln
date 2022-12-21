#include <ctime>

KrnlnApi int 取时间部分(const std::tm& 欲取其部分的时间, int 欲取的时间部分) {
	int ret = 0;
	switch (欲取的时间部分) {
	case 1: // 年份
		ret = 欲取其部分的时间.tm_year + 1900; // tm_year 存储的是年份减去 1900 的值
		break;
	case 2: // 季度
		ret = (欲取其部分的时间.tm_mon + 1) / 3; // tm_mon 存储的是月份减去 1 的值
		break;
	case 3: // 月份
		ret = 欲取其部分的时间.tm_mon + 1; // tm_mon 存储的是月份减去 1 的值
		break;
	case 4: // 自年首周数
		ret = 欲取其部分的时间.tm_yday / 7 + 1; // tm_yday 存储的是当前日期是从一年开始的第几天
		break;
	case 5: // 日
		ret = 欲取其部分的时间.tm_mday;
		break;
	case 6: // 小时
		ret = 欲取其部分的时间.tm_hour;
		break;
	case 7: // 分钟
		ret = 欲取其部分的时间.tm_min;
		break;
	case 8: // 秒
		ret = 欲取其部分的时间.tm_sec;
		break;
	case 9: // 星期几
		ret = 欲取其部分的时间.tm_wday + 1; // tm_wday 存储的是星期几减去 1 的值
		break;
	case 10: // 自年首天数
		ret = 欲取其部分的时间.tm_yday + 1; // tm_yday 存储的是当前日期是从一年开始的第几天
		break;
	}
	return ret;
}