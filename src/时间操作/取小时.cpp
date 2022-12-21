#include<ctime>


KrnlnApi int 取小时(const std::tm& 时间) {
	// 使用 std::tm 结构体中的 tm_hour 字段来获取小时
	return 时间.tm_hour;
}
