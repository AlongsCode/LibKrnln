#include<string>

#ifdef _WIN32

#include"windows.h"
using namespace std;
KrnlnApi long long 取磁盘剩余空间(const string& 磁盘驱动器字符) {
	char DirName[MAX_PATH] = { 0 };
	if (磁盘驱动器字符 == "")
	{
		if (GetCurrentDirectoryA(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = 0;

	}
	else
	{
		if (磁盘驱动器字符.empty())
			return -1;

		DirName[0] = *磁盘驱动器字符.c_str();
		DirName[1] = ':';
		DirName[2] = 0;

	}
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExA(DirName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
	{
		long long nRet = (long long)(FreeBytesAvailableToCaller.QuadPart / 1024);
		return nRet;
	}
	return -1;
}

KrnlnApi long long 取磁盘剩余空间(const wstring& 磁盘驱动器字符) {
	wchar_t DirName[MAX_PATH] = { 0 };
	if (磁盘驱动器字符.empty())
	{
		if (GetCurrentDirectoryW(MAX_PATH, DirName) == 0)
			return -1;
		DirName[2] = L'\0';

	}
	else
	{
		if (磁盘驱动器字符.empty())
			return -1;

		DirName[0] = *磁盘驱动器字符.c_str();
		DirName[1] = L':';
		DirName[2] = L'\0';

	}
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;

	if (GetDiskFreeSpaceExW(DirName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
	{
		long long nRet = (long long)(FreeBytesAvailableToCaller.QuadPart / 1024);
		return nRet;
	}
	return -1;
}


KrnlnApi long long 取磁盘剩余空间(char 磁盘驱动器字符) {
	char DirName[4] = { 0 };
	DirName[0] = 磁盘驱动器字符;
	DirName[1] = ':';
	DirName[2] = 0;
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExA(DirName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
	{
		long long nRet = (long long)(FreeBytesAvailableToCaller.QuadPart / 1024);
		return nRet;
	}
	return -1;
}

KrnlnApi long long 取磁盘剩余空间(wchar_t 磁盘驱动器字符) {
	wchar_t DirName[4] = { 磁盘驱动器字符,L':' };
	DirName[0] = 磁盘驱动器字符;
	DirName[1] = L':';
	DirName[2] = L'\0';
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	if (GetDiskFreeSpaceExW(DirName, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
	{
		long long nRet = (long long)(FreeBytesAvailableToCaller.QuadPart / 1024);
		return nRet;
	}
	return -1;
}
#endif // _WIN32



