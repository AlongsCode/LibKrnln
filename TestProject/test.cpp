
#define 调试版
#include"..\include\krnln.h"




//寻找文本速度对比
//int main() {
//	std::string S = "sadbutsdsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsafwaewadsaadt = formatted_text.find(f", N = "tsdsadsatsdsadsatsdsadsaafsafwaewadsaadt = formatted_text.find(f";
//	intptr_t  A, B, ret = 0;
//	size_t i;
//	A = GetTickCount();
//	for (i = 0; i < 9999999; i++)
//	{
//		ret = 寻找文本(S, N, 0, false);
//	}
//	B = GetTickCount();
//	标准输出(0, "速度:" + std::to_string(B - A) + "位置:" + to_string(ret) + " " + std::to_string(i));
//}


//int main() {
//
//	数组 < 文本型 > A = { L"测试",L"测试",L"测试" }, B = { L"测试2" ,L"测试2" ,L"测试2" };
//	调试输出(A + B);
//	return 0;
//}




//int main() {
//	std::vector<int> fruits = { 2,71, 45,11,32, 674,88, 5465,946 ,8676 };
//	数组排序(fruits);
//	int index = 二分查找(fruits, 8676);
//	if (index != -1) {
//		std::cout << "Found cherry at index " << fruits[index] << std::endl;
//	}
//	else {
//		std::cout << "Cherry not found" << std::endl;
//	}
//	return 0;
//}

#ifdef _WIN32
#include <windows.h>
#include"tlhelp32.h"
#else
#include <unistd.h>
#include <sys/wait.h>
#endif
bool 终止进程(std::string process_name_or_window_title) {
	// 用于存储进程 ID 的变量
	unsigned int process_id = 0;

	// 在 Windows 系统上使用 FindWindow 函数查找窗口句柄
#ifdef _WIN32
	HWND window_handle = FindWindowA(0, process_name_or_window_title.c_str());
	if (window_handle) {
		GetWindowThreadProcessId(window_handle, (LPDWORD)&process_id);
	}
#else
	 // 使用 ps 命令查找进程 ID
	std::string command = "pidof " + process_name_or_window_title;
	std::FILE* process_id_file = std::popen(command.c_str(), "r");
	if (process_id_file) {
		std::fscanf(process_id_file, "%d", &process_id);
		std::pclose(process_id_file);
	}
#endif
	// 如果没有找到进程 ID，返回 false
	if (process_id == 0) {
		return false;
	}

	// 在 Windows 系统上使用 TerminateProcess 函数终止进程
#ifdef _WIN32
	HANDLE process_handle = OpenProcess(PROCESS_TERMINATE, 0, process_id);
	bool result = TerminateProcess(process_handle, 0) == TRUE;
	return result;
#else
	int kill_result = std::system(("kill " + std::to_string(process_id)).c_str());
	// 如果 kill 命令返回 0，表示成功终止进程
	return kill_result == 0;
#endif
}



int main()
{
	调试输出(终止进程(21620));
	return 0;
}
