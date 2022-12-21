#include"string"
#include"windows.h"
using namespace std;

KrnlnApi long long 取文件尺寸(const string& 文件名)
{
	WIN32_FIND_DATAA inf;
	const HANDLE handle = ::FindFirstFileA(文件名.c_str(), &inf);
	if (handle != INVALID_HANDLE_VALUE) {
		::FindClose(handle);
		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
	}
	return -1;
}
KrnlnApi long long 取文件尺寸(const wstring& 文件名) {
	WIN32_FIND_DATAW inf;
	const HANDLE handle = ::FindFirstFileW(文件名.c_str(), &inf);
	if (handle != INVALID_HANDLE_VALUE) {
		::FindClose(handle);
		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
	}
	return -1;
}


