#include<ctime>


KrnlnApi int 取星期几(const std::tm& 时间) {
	return  时间.tm_wday + 1;
}