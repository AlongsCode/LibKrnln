#include <chrono>
#include <iomanip>
#include <sstream>

KrnlnApi std::tm 取现行时间() {
	// 获取当前时间
	auto now = std::chrono::system_clock::now();
	// 将时间转换为本地时间，并舍入到最接近的秒
	auto localTime = std::chrono::floor<std::chrono::seconds>(now);
	// 将时间点转换为 time_t 对象
	auto time = std::chrono::system_clock::to_time_t(localTime);
	// 将 time_t 对象转换为 std::tm 对象
	std::tm tm;
	localtime_s(&tm, &time);
	return tm;
}
