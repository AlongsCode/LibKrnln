#include<string>
#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif


#ifdef _WIN32
KrnlnApi void 禁止重复运行(const std::wstring& identifier, void(*callback)())
{
	if (OpenEventW(EVENT_ALL_ACCESS, false, identifier.c_str())) {

		if (callback) {
			callback();
		}
		exit(0);
	}
	CreateEventW(NULL, false, false, identifier.c_str());
}
KrnlnApi void 禁止重复运行(const std::string& identifier, void(*callback)())
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
KrnlnApi void 禁止重复运行(const std::string& identifier, void(*callback)())
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
KrnlnApi void 禁止重复运行(const std::wstring& identifier, void(*callback)())
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