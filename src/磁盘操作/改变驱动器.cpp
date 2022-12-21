//#include"string"
//
//#ifdef _WIN32
//#include<windows.h>
//#else///Linux,UNIX
//#include<direct.h>
//#define SetCurrentDirectoryW(dir) _wchdir(dir)
//#define SetCurrentDirectoryA(dir) chdir(dir)
//#endif 
//using namespace std;
//KrnlnApi bool 改变驱动器(char 欲改变到的驱动器) {
//	char DirName[4] = { 欲改变到的驱动器, ':', '\\', 0 };;
//	return SetCurrentDirectoryA(DirName);
//}
//KrnlnApi bool 改变驱动器(wchar_t 欲改变到的驱动器) {
//	wchar_t DirName[4] = { 欲改变到的驱动器, L':', L'\\', 0 };
//	return SetCurrentDirectoryW(DirName);
//}
//
//
//KrnlnApi bool 改变驱动器(const string& 欲改变到的驱动器) {
//	if (!欲改变到的驱动器.empty()) {
//		char DirName[4] = { *欲改变到的驱动器.c_str(), ':', '\\', 0 };
//		return SetCurrentDirectoryA(DirName);
//	}
//	return false;
//}
//
//
//KrnlnApi bool 改变驱动器(const wstring& 欲改变到的驱动器) {
//	if (!欲改变到的驱动器.empty()) {
//		wchar_t DirName[4] = { *欲改变到的驱动器.c_str(), L':', L'\\', 0 };
//		return SetCurrentDirectoryW(DirName);
//	}
//	return false;
//}



//对于不支持C++17不再兼容，标准库实现更方便更安全
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

KrnlnApi bool 改变驱动器(char drive) {
	try {
		std::string dir_name = { drive, ':', '/' };
		fs::current_path(dir_name);
		return true;
	}
	catch (const fs::filesystem_error) {
		return false;
	}
}

KrnlnApi bool 改变驱动器(wchar_t drive) {
	try {
		std::wstring dir_name = { drive, L':', L'/' };
		fs::current_path(dir_name);
		return true;
	}
	catch (const fs::filesystem_error) {
		return false;
	}
}

KrnlnApi bool 改变驱动器(const std::string& drive) {
	if (!drive.empty()) {
		try {
			std::string dir_name = { drive[0], ':', '/' };
			fs::current_path(dir_name);
			return true;
		}
		catch (const fs::filesystem_error) {
			return false;
		}
	}
	return false;
}

KrnlnApi bool 改变驱动器(const std::wstring& drive) {
	if (!drive.empty()) {
		try {
			std::wstring dir_name = { drive[0], L':', L'/' };
			fs::current_path(dir_name);
			return true;
		}
		catch (const fs::filesystem_error) {
			return false;
		}
	}
	return false;
}

