
#include <ctime>
#include <algorithm> 
KrnlnApi std::tm 指定时间(int year, int month, int day, int hour, int minute, int second)
{
	// Set the year
	year = std::clamp(year, 100, 9999);
	// 设置月份
	month = std::clamp(month, 1, 12);

	// 计算当前月份的天数
	int max_day = 0;
	if (month == 2)
	{
		// 二月
		bool is_leap_year = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
		max_day = is_leap_year ? 29 : 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		// 四月、六月、九月、十一月
		max_day = 30;
	}
	else
	{
		// 其他月份都是31天
		max_day = 31;
	}

	// 设置日期
	day = std::clamp(day, 1, max_day);

	// 设置小时
	hour = std::clamp(hour, 0, 23);

	// 设置分钟
	minute = std::clamp(minute, 0, 59);

	// 设置秒钟
	second = std::clamp(second, 0, 59);

	// 创建std::tm对象
	std::tm time;
	time.tm_year = year - 1900;
	time.tm_mon = month - 1;
	time.tm_mday = day;
	time.tm_hour = hour;
	time.tm_min = minute;
	time.tm_sec = second;

	return time;
}