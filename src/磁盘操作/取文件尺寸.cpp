//
//
//#ifdef _WIN32
//#include<string>
//#include<windows.h>
//using namespace std;
//KrnlnApi long long 取文件尺寸(const string& filename)
//{
//	WIN32_FIND_DATAA inf;
//	const HANDLE handle = ::FindFirstFileA(filename.c_str(), &inf);
//	if (handle != INVALID_HANDLE_VALUE) {
//		::FindClose(handle);
//		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
//	}
//	return -1;
//}
//KrnlnApi long long 取文件尺寸(const wstring& filename) {
//	WIN32_FIND_DATAW inf;
//	const HANDLE handle = ::FindFirstFileW(filename.c_str(), &inf);
//	if (handle != INVALID_HANDLE_VALUE) {
//		::FindClose(handle);
//		return (((INT64)inf.nFileSizeHigh << 32) | (INT64)inf.nFileSizeLow);
//	}
//	return -1;
//}
//
//
//
//
//
//
//#else
#include <filesystem>
KrnlnApi long long 取文件尺寸(const std::string& filename) {
	if (!std::filesystem::exists(filename)) {
		return -1;
	}

	return std::filesystem::file_size(filename);
}

KrnlnApi long long 取文件尺寸(const std::wstring& filename) {
	if (!std::filesystem::exists(filename)) {
		return -1;
	}

	return std::filesystem::file_size(filename);
}

//#endif 





