#include <chrono>
#include <thread>

/*
本命令暂停当前程序的运行并等待指定的时间
<int> 类型变量 <欲等待的时间> 本参数指定欲暂停程序执行的时间，单位为毫秒
*/
KrnlnApi void 延时(long long 欲等待的时间) {
	if (欲等待的时间 <= 0) {
		return;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(欲等待的时间));
}
