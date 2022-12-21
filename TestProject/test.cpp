
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


#include<iostream>
void* mutex = nullptr;
void thread_func(void* arg)
{
	int* thread_num = static_cast<int*>(arg);
	std::cout << "Thread " << *thread_num << " running" << std::endl;

	// 使用互斥体保护共享资源

	进入许可区(mutex);
	// 使用共享资源
	std::cout << "Thread " << *thread_num << " using shared resource" << std::endl;
	退出许可区(mutex);

	std::cout << "Thread " << *thread_num << " exiting" << std::endl;
}

int main()
{
	mutex = 创建进入许可证();
	int thread1_num = 1, thread2_num = 2;
	void* thread1_handle = 启动线程(thread_func, &thread1_num);
	void* thread2_handle = 启动线程(thread_func, &thread2_num);

	// 等待两个线程结束
	等待线程(thread1_handle);
	等待线程(thread2_handle);

	// 关闭线程句柄
	关闭线程句柄(thread1_handle);
	关闭线程句柄(thread2_handle);

	// 释放互斥体资源
	删除进入许可证(mutex);

	return 0;
}

























