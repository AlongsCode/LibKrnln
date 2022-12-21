#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
KrnlnApi std::tm 到时间(const std::string& s) {
	// 默认时间值
	std::tm default_time{};
	default_time.tm_year = 100;
	default_time.tm_mon = 1;
	default_time.tm_mday = 1;

	// 如果参数本身就是时间数据，直接返回
	std::tm time{};
	std::istringstream input(s);
	input >> std::get_time(&time, "%Y年%m月%d日%H时%M分%S秒");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y/%m/%d %H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y/%m/%d/%H/%M/%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y/%m/%d/%H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y-%m-%d-%H-%M-%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y-%m-%d-%H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y.%m.%d %H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, "%Y%m%d%H%M%S");
	if (!input.fail()) {
		return time;
	}

	// 如果文本不符合格式要求或者时间值错误，返回默认时间值
	return default_time;
}
KrnlnApi std::tm 到时间(const std::wstring& s) {
	// 默认时间值
	std::tm default_time{};
	default_time.tm_year = 100;
	default_time.tm_mon = 1;
	default_time.tm_mday = 1;

	// 如果参数本身就是时间数据，直接返回
	std::tm time{};
	std::wistringstream input(s);
	input >> std::get_time(&time, L"%Y年%m月%d日%H时%M分%S秒");
	if (!input.fail()) {
		return time;
	}

	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y/%m/%d %H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y/%m/%d/%H/%M/%S");
	if (!input.fail()) {
		return time;
	}

	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y/%m/%d/%H:%M:%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y-%m-%d-%H-%M-%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y-%m-%d-%H:%M:%S");
	if (!input.fail()) {
		return time;
	}

	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y.%m.%d %H:%M:%S");
	if (!input.fail()) {
		return time;
	}

	input.clear();
	input.str(s);
	input >> std::get_time(&time, L"%Y%m%d%H%M%S");
	if (!input.fail()) {
		return time;
	}
	input.clear();
	input.str(s);

	input >> std::get_time(&time, L"%Y%m%d%H%M%S");
	if (!input.fail()) {
		return time;
	}
	// 如果文本不符合格式要求或者时间值错误，返回默认时间值
	return default_time;
}


