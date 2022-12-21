

#ifdef _WIN32
#include<string>
#include<windows.h>
using namespace std;
KrnlnApi long long 取文件尺寸(const string& filename)
{
	WIN32_FIND_DATAA inf;
	const HANDLE handle = ::FindFirstFileA(filename.c_str(), &inf);
	if (handle != INVALID_HANDLE_VALUE) {
		::FindClose(handle);
		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
	}
	return -1;
}
KrnlnApi long long 取文件尺寸(const wstring& filename) {
	WIN32_FIND_DATAW inf;
	const HANDLE handle = ::FindFirstFileW(filename.c_str(), &inf);
	if (handle != INVALID_HANDLE_VALUE) {
		::FindClose(handle);
		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
	}
	return -1;
}
#else
#include <fstream>
KrnlnApi long long 取文件尺寸(const std::string& filename) {
	std::ifstream fp(filename, std::ios::binary);
	if (!fp.is_open()) {
		return -1;
	}

	fp.seekg(0, std::ios::end);
	long long size = fp.tellg();
	fp.close();
	return size;
}

KrnlnApi long long 取文件尺寸(const std::wstring& filename) {
	std::wifstream fp(filename, std::ios::binary);
	if (!fp.is_open()) {
		return -1;
	}

	fp.seekg(0, std::ios::end);
	long long size = fp.tellg();
	fp.close();
	return size;
}

#endif 





