//宏定义仅仅是方便维护，编译器不支持utf8或unicode可以去掉
#define 年份 1
#define 季度 2
#define 月份 3
#define 周 4
#define 日 5
#define 小时 6
#define 分钟 7
#define 秒 8
#include <ctime>
int GetDaysOfSpecMonth(int year, int month)
{
	//定义一个数组，包含每个月的天数
	const int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// 如果是闰年，二月份的天数为 29 天
	if (((year % 400 == 0) || (year % 100 != 0) && (year % 4 == 0)) && month == 2)
	{
		return 29;
	}

	// 返回月份的天数
	return daysPerMonth[month - 1];
}
KrnlnApi std::tm 增减时间(const std::tm& 时间, int 被增加部分, int 增加值)
{
	std::tm newTime = 时间;
	switch (被增加部分)
	{
	case 年份: // 年份
	{
		newTime.tm_year += 增加值;
		if (newTime.tm_mon == 2 && newTime.tm_mday == 29)
			newTime.tm_mday = GetDaysOfSpecMonth(newTime.tm_year, 2);
		break;
	}
	case 季度: // 季度
	{
		int nMonth = newTime.tm_mon + (增加值 * 3);
		if (nMonth > 0)
		{
			newTime.tm_year += (nMonth / 12);
			nMonth %= 12;
		}
		else
		{
			int decYear = nMonth / 12;
			if (nMonth % 12 != 0)
				decYear--;
			newTime.tm_year += decYear;
			nMonth = 12 + (nMonth % 12);
		}
		newTime.tm_mon = nMonth;

		int nMaxDay = GetDaysOfSpecMonth(newTime.tm_year, nMonth);
		if (newTime.tm_mday > nMaxDay)
			newTime.tm_mday = nMaxDay;
		break;
	}
	case 月份: // 月份
	{
		int nMonth = newTime.tm_mon + 增加值;
		if (nMonth > 0)
		{
			newTime.tm_year += (nMonth / 12);
			nMonth %= 12;
		}
		else
		{
			int decYear = nMonth / 12;
			if (nMonth % 12 != 0)
				decYear--;
			newTime.tm_year += decYear;
			nMonth = 12 + (nMonth % 12);
		}
		newTime.tm_mon = nMonth;
		int nMaxDay = GetDaysOfSpecMonth(newTime.tm_year, nMonth);
		if (newTime.tm_mday > nMaxDay)
			newTime.tm_mday = nMaxDay;
		break;
	}
	case 周: // 周
	{
		int nDay = newTime.tm_mday + (增加值 * 7);
		int nMaxDay = GetDaysOfSpecMonth(newTime.tm_year, newTime.tm_mon);
		if (nDay > nMaxDay)
		{
			nDay -= nMaxDay;
			newTime = 增减时间(newTime, 月份, 1);
		}
		newTime.tm_mday = nDay;
		break;
	}
	case 日: // 日
	{
		newTime.tm_mday += 增加值;
		int nMaxDay = GetDaysOfSpecMonth(newTime.tm_year, newTime.tm_mon);
		if (newTime.tm_mday > nMaxDay)
		{
			newTime.tm_mday -= nMaxDay;
			newTime = 增减时间(newTime, 月份, 1);
		}
		break;
	}
	case 小时: // 小时
	{
		newTime.tm_hour += 增加值;
		if (newTime.tm_hour >= 24)
		{
			newTime.tm_hour -= 24;
			newTime = 增减时间(newTime, 日, 1);
		}
		break;
	}
	case 分钟: // 分钟
	{
		newTime.tm_min += 增加值;
		if (newTime.tm_min >= 60)
		{
			newTime.tm_min -= 60;
			newTime = 增减时间(newTime, 小时, 1);
		}
		break;
	}
	default://其他情况都为秒
		newTime.tm_sec += 增加值;
		if (newTime.tm_sec >= 60)
		{
			newTime.tm_sec -= 60;
			newTime = 增减时间(newTime, 分钟, 1);
		}
		break;
	}
	return newTime;
}


