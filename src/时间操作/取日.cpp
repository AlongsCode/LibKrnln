#include<ctime>
KrnlnApi int 取日(const std::tm& 时间) {
	return 时间.tm_mday;
}