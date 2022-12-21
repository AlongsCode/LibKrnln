
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
void 禁止重复运行(const std::string& identifier, void(*callback)())
{
	pthread_mutex_t mutex;
	if (pthread_mutex_init(&mutex, NULL) != 0 || pthread_mutex_lock(&mutex) != 0) {

		if (callback) {
			callback();
		}
		exit(0);
	}
}
void 禁止重复运行(const std::wstring& identifier, void(*callback)())
{
	pthread_mutex_t mutex;
	if (pthread_mutex_init(&mutex, NULL) != 0 || pthread_mutex_lock(&mutex) != 0) {

		if (callback) {
			callback();
		}
		exit(0);
	}
}
#endif
#pragma endregion

//#include <memory>
//#include <thread>
//#include <atomic>
//#include<vector>
//bool 创建线程(void* 欲执行的子程序, void* 参数数据, HANDLE* 线程句柄) {
//	void* arg = nullptr, * hThread;;
//	bool ret;
//	if (参数数据)
//		arg = 参数数据;
//	hThread = CreateThread(0, 0, *(LPTHREAD_START_ROUTINE*)欲执行的子程序, arg, 0, 0);
//	ret = hThread != 0;
//	if (hThread && 线程句柄) {
//		*线程句柄 = hThread;
//	}
//	else {
//		if (hThread) {
//			CloseHandle(hThread);//提前释放资源，不然不保存导致悬浮指针后面无法清理
//		}
//	}
//}
//
//typedef void (*function)(int);
//
//LPCRITICAL_SECTION 创建进入许可证()
//{
//	LPCRITICAL_SECTION v1 = new RTL_CRITICAL_SECTION;
//	InitializeCriticalSection(v1);
//	return v1;
//}
//#include<iostream>
//void foo()
//{
//	while (true)
//	{
//		std::cout << "start run  " << endl;
//		Sleep(500);
//	}
//
//
//}
//using SubPtr = void (*)(int);
//
//bool 线程启动(SubPtr function, int data, thread** pRet)
//{
//	try
//	{
//		int arg = data == 0 ? 0 : data;
//		std::thread* thread = new std::thread(function, arg);
//		thread->detach();
//		if (pRet)
//		{
//			*pRet = thread;
//		}
//		return true;
//	}
//	catch (const std::system_error& e)
//	{
//
//		MessageBoxW(GetActiveWindow(), L"启动线程失败", L"异常", 0);
//		return false;
//	}
//}
//bool 进入临界区(LPCRITICAL_SECTION cs) {
//	EnterCriticalSection(cs);
//}
//bool 退出临界区(LPCRITICAL_SECTION cs) {
//
//	LeaveCriticalSection(cs);
//}
//bool 退出临界区(LPCRITICAL_SECTION cs) {
//
//	DeleteCriticalSection(cs);
//}
//bool 等待线程(HANDLE cs, int time) {
//	time = time > 0 ? time : -1;//最大等待时长
//	WaitForSingleObject(cs, time);
//}
//bool 强制结束线程(HANDLE cs) {
//	DWORD ExitCode;
//	GetExitCodeThread(cs, &ExitCode);
//	return TerminateThread(cs, ExitCode);
//}
#include <filesystem>
long long _取文件尺寸(const std::string& filename) {
	if (!std::filesystem::exists(filename)) {
		return -1;
	}

	return std::filesystem::file_size(filename);
}




int main() {


}




























