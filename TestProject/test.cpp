
#define 调试版
#include"..\include\krnln.h"


#pragma region 禁止程序重复运行
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif


#ifdef _WIN32
void 禁止重复运行(const std::wstring& identifier, void(*callback)())
{
	if (OpenEventW(EVENT_ALL_ACCESS, false, identifier.c_str())) {

		if (callback) {
			callback();
		}

		exit(0);
	}
	CreateEventW(NULL, false, false, identifier.c_str());
}
void 禁止重复运行(const std::string& identifier, void(*callback)())
{
	if (OpenEventA(EVENT_ALL_ACCESS, false, identifier.c_str())) {

		if (callback) {
			callback();
		}
		exit(0);
	}
	CreateEventA(NULL, false, false, identifier.c_str());
}
#else
#include<sys/file.h>
void 禁止重复运行(const std::string& identifier, void(*callback)())
{
	std::string lock_file = identifier + ".lock";
	int fd = open(lock_file.c_str(), O_CREAT | O_WRONLY, 0644);
	if (fd < 0) {
		if (callback) {
			callback();
		}
		exit(0);
	}
	if (lockf(fd, F_TLOCK, 0) < 0) {
		if (callback) {
			callback();
		}
		exit(0);
	}
}
void 禁止重复运行(const std::wstring& identifier, void(*callback)())
{
	std::wstring lock_file = identifier + L".lock";
	int fd = wopen(lock_file.c_str(), O_CREAT | O_WRONLY, 0644);
	if (fd < 0) {
		if (callback) {
			callback();
		}
		exit(0);
	}
	if (lockf(fd, F_TLOCK, 0) < 0) {
		if (callback) {
			callback();
		}
		exit(0);
	}
}
#endif
#pragma endregion



int wmain() {
	//字节集 S = 到字节集("sadbutsdsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsaafsafwaewadsaad"), N = 到字节集("fwaewadsa");
	//int A, B, 位置变量;
	//A = GetTickCount64();
	//for (size_t i = 0; i < 9999999; i++)
	//{
	//	寻找字节集(到字节集("leetcode"), 到字节集("leeto"));
	//}
	//B = GetTickCount64();

	//调试输出("速度:" + 到文本A(B - A), 寻找字节集(S, N));
	//A = GetTickCount64();
	//for (size_t i = 0; i < 9999999; i++)
	//{
	//	strStr(S, N);
	//}
	//B = GetTickCount64();
	//if
	//调试输出("速度:" + 到文本A(B - A), 寻找字节集(S, N));



}




















