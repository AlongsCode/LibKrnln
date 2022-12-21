#include<ctime>




/*
返回一个值为 1 到 12 之间的整数，表示指定时间中的月份
<void*> 类型变量 <时间>

*/
KrnlnApi int 取月份(const std::tm& 时间) {
	// 使用 std::tm 结构体中的 tm_mon 字段来获取月份
	return 时间.tm_mon + 1;
}