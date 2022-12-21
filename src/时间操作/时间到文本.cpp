
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
KrnlnApi std::wstring 时间到文本W(const std::tm& 欲转换到文本的时间, int 转换部分, bool 是否中文)
{
	std::wstringstream ss;
	if (转换部分 == 1) { // 转换日期部分
		ss << std::put_time(&欲转换到文本的时间, 是否中文 ? L"%Y年%m月%d日" : L"%m/%d/%Y");
	}
	else if (转换部分 == 2) { // 转换时间部分
		if (转换部分 == 0) {
			ss << (是否中文 ? L" " : L" ");
		}
		if (欲转换到文本的时间.tm_sec != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? L"%H时%M分%S秒" : L"%I:%M:%S %p");
		}
		else if (欲转换到文本的时间.tm_min != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? L"%H时%M分" : L"%I:%M %p");
		}
		else if (欲转换到文本的时间.tm_hour != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? L"%H时" : L"%I %p");
		}
	}
	else {//全部转换
		ss << std::put_time(&欲转换到文本的时间, 是否中文 ? L"%Y年%m月%d日 %H时%M分%S秒" : L"%m/%d/%Y %I:%M:%S %p");
	}
	return ss.str();
}


KrnlnApi std::string 时间到文本A(const std::tm& 欲转换到文本的时间, int 转换部分, bool 是否中文)
{
	std::stringstream ss;
	ss.imbue(std::locale("zh_CN.UTF-8"));
	if (转换部分 == 1) { // Convert date part
		ss << std::put_time(&欲转换到文本的时间, 是否中文 ? "%Y年%m月%d日" : "%m/%d/%Y");
	}
	else if (转换部分 == 2) { // Convert time part
		if (转换部分 == 0) {
			ss << (是否中文 ? " " : " ");
		}
		if (欲转换到文本的时间.tm_sec != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? "%H时%M分%S秒" : "%I:%M:%S %p");
		}
		else if (欲转换到文本的时间.tm_min != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? "%H时%M分" : "%I:%M %p");
		}
		else if (欲转换到文本的时间.tm_hour != 0) {
			ss << std::put_time(&欲转换到文本的时间, 是否中文 ? "%H时" : "%I %p");
		}
	}
	else {// Convert all
		ss << std::put_time(&欲转换到文本的时间, 是否中文 ? "%Y年%m月%d日 %H时%M分%S秒" : "%m/%d/%Y %I:%M:%S %p");
	}
	ss.imbue(std::locale("zh_CN.UTF-8"));
	return ss.str();
}