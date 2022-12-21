
#include <ctime>
#include <cmath>
#include <cstdio>

// 计算两个时间之间的秒数
double secondsBetween(const std::tm& time1, const std::tm& time2) {
	double seconds = std::difftime(std::mktime(const_cast<std::tm*>(&time1)), std::mktime(const_cast<std::tm*>(&time2)));
	return seconds < 0 ? -seconds : seconds;
}

// 计算两个时间之间的年份
int yearsBetween(const std::tm& time1, const std::tm& time2) {
	// 检查日期是否合法
	if (time1.tm_mon < 1 || time1.tm_mon > 12 ||
		time1.tm_mday < 1 || time1.tm_mday > 31 ||
		time2.tm_mon < 1 || time2.tm_mon > 12 ||
		time2.tm_mday < 1 || time2.tm_mday > 31) {
		return 0; // 返回0
	}
	const int START_YEAR = 1900;
	int ygap = 0;
	if (time1.tm_year > time2.tm_year) {
		// 计算 time1 到 time2 的年数差
		ygap = time1.tm_year - time2.tm_year;

		// 计算 time1 到 time2 的天数差
		int days1 = 0;
		for (int i = time2.tm_year; i < time1.tm_year; i++) {
			if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
				// 闰年
				days1 += 366;
			}
			else {
				// 平年
				days1 += 365;
			}
		}
		days1 += time1.tm_yday - time2.tm_yday;

		// 如果天数差小于一年，则减少一年
		if (days1 < 365) {
			ygap--;
		}
	}
	else if (time1.tm_year < time2.tm_year) {
		// 计算 time2 到 time1 的年数差
		ygap = time2.tm_year - time1.tm_year;

		// 计算 time2 到 time1 的天数差
		int days2 = 0;
		for (int i = time1.tm_year; i < time2.tm_year; i++) {
			if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
				// 闰年
				days2 += 366;
			}
			else {
				// 平年
				days2 += 365;
			}
		}
		days2 += time2.tm_yday - time1.tm_yday;
		// 如果天数差小于一年，则减少一年
		if (days2 < 365) {
			ygap--;
		}
	}

	return ygap;
}

// 计算两个时间之间的季度
double quartersBetween(const std::tm& time1, const std::tm& time2) {
	int gap = 12 * (time1.tm_year - time2.tm_year) + time1.tm_mon - time2.tm_mon;
	gap = gap < 0 ? -gap : gap;
	return std::ceil(gap / 3.0);
}

// 计算两个时间之间的月份
int monthsBetween(const std::tm& time1, const std::tm& time2) {
	int gap = 12 * (time1.tm_year - time2.tm_year) + time1.tm_mon - time2.tm_mon;
	if (gap < 0) {
		gap *= -1;  // 将秒数取为正数
	}
	// 判断时间差距是否足一个月份
	if (time1.tm_mday < time2.tm_mday) {
		gap--;
	}
	return gap;
}

// 计算两个时间之间的周数
double weeksBetween(const std::tm& time1, const std::tm& time2) {
	double seconds = secondsBetween(time1, time2);
	return std::floor(seconds / (604800.0));
}

// 计算两个时间之间的天数
double daysBetween(const std::tm& time1, const std::tm& time2) {
	double seconds = secondsBetween(time1, time2);
	return std::floor(seconds / 86400.0);
}

// 计算两个时间之间的小时数
double hoursBetween(const std::tm& time1, const std::tm& time2) {
	double seconds = secondsBetween(time1, time2);
	return std::floor(seconds / 3600.0);
}

// 计算两个时间之间的分钟数
double minutesBetween(const std::tm& time1, const std::tm& time2) {
	double seconds = secondsBetween(time1, time2);
	return std::floor(seconds / 60.0);
}


// 计算两个时间之间的间隔
KrnlnApi double 取时间间隔(const std::tm& time1, const std::tm& time2, int interval) {
	switch (interval) {
	case 1: return yearsBetween(time1, time2);
	case 2: return quartersBetween(time1, time2);
	case 3: return monthsBetween(time1, time2);
	case 4: return weeksBetween(time1, time2);
	case 5: return daysBetween(time1, time2);
	case 6: return hoursBetween(time1, time2);
	case 7: return minutesBetween(time1, time2);
	default: return secondsBetween(time1, time2);//其余情况默认返回秒数
	}
}
