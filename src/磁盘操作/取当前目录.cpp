#include<string>
#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi string 取当前目录A() {

	char DirName[MAX_PATH] = { 0 };
	string pText;
	if (GetCurrentDirectoryA(MAX_PATH, DirName))
	{
		return DirName;
	}
	return string();
}
KrnlnApi wstring 取当前目录W() {
	wchar_t DirName[MAX_PATH] = { 0 };
	if (GetCurrentDirectoryW(MAX_PATH, DirName))
	{
		return DirName;
	}
	return wstring();
}

#else
#include"direct.h"
KrnlnApi string 取当前目录A()
{
	char  pBuff[0x400] = { 0 };
	if (_getcwd(pBuff, 0x400)) {
		return pBuff;
	}
	return string();
}
KrnlnApi wstring 取当前目录W() {
	wchar_t  pBuff[0x400] = { 0 };
	if (_wgetcwd(pBuff, 0x400)) {
		return pBuff;
	}
	return wstring();

}
#endif