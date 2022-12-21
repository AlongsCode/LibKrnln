#include"string"
#ifdef _WIN32
#include<windows.h>
using namespace std;

KrnlnApi long long 取磁盘总空间(wchar_t 磁盘驱动器字符) {
	wchar_t DirName[4] = { 0 };
	DirName[0] = 磁盘驱动器字符;
	DirName[1] = L':';
	DirName[2] = L'\0';
	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	return (GetDiskFreeSpaceExW(DirName, &i64FreeBytesToCaller, &i64TotalBytes, &i64FreeBytes) ? (long long)i64TotalBytes.QuadPart / 1024 : -1);
}
KrnlnApi long long 取磁盘总空间(char 磁盘驱动器字符) {
	char DirName[4] = { 0 };
	DirName[0] = 磁盘驱动器字符;
	DirName[1] = ':';
	DirName[2] = '\0';
	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	return (GetDiskFreeSpaceExA(DirName, &i64FreeBytesToCaller, &i64TotalBytes, &i64FreeBytes) ? (long long)i64TotalBytes.QuadPart / 1024 : -1);
}
KrnlnApi long long 取磁盘总空间(const string& 磁盘驱动器字符) {

	char DirName[MAX_PATH] = { 0 };
	if (磁盘驱动器字符.empty())
	{
		if (GetCurrentDirectoryA(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = 0;
	}
	else
	{
		DirName[0] = *磁盘驱动器字符.c_str();
		DirName[1] = ':';
		DirName[2] = '\0';

	}
	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	return (GetDiskFreeSpaceExA(DirName, &i64FreeBytesToCaller, &i64TotalBytes, &i64FreeBytes) ? (INT64)i64TotalBytes.QuadPart / 1024 : -1);
}



KrnlnApi long long 取磁盘总空间(const wstring& 磁盘驱动器字符) {

	wchar_t DirName[MAX_PATH] = { 0 };
	if (磁盘驱动器字符.empty())
	{
		if (GetCurrentDirectoryW(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = 0;
	}
	else
	{
		DirName[0] = *磁盘驱动器字符.c_str();
		DirName[1] = L':';
		DirName[2] = L'\0';

	}
	//ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	ULARGE_INTEGER i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes;
	return (GetDiskFreeSpaceExW(DirName, &i64FreeBytesToCaller, &i64TotalBytes, &i64FreeBytes) ? (INT64)i64TotalBytes.QuadPart / 1024 : -1);
}

#endif // _WIN32