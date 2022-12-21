#include<string>
#ifdef _WIN32
#include<windows.h>
#else
#include<direct.h>
#endif
using namespace std;
KrnlnApi bool 改变目录(const string& 欲改变到的目录) {
#ifdef _WIN32
	return SetCurrentDirectoryA(欲改变到的目录.c_str());
#else
	return _chdir(目录.c_str()) == 0;
#endif
}
KrnlnApi bool 改变目录(const wstring& 欲改变到的目录) {
#ifdef _WIN32
	return SetCurrentDirectoryW(欲改变到的目录.c_str());
#else
	return _wchdir(目录.c_str()) == 0;
#endif
}
