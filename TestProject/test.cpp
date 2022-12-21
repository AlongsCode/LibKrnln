
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


#include <filesystem>
long long _取文件尺寸(const std::string& filename) {
	if (!std::filesystem::exists(filename)) {
		return -1;
	}

	return std::filesystem::file_size(filename);
}




int main() {


}




























