

#include<string>
#ifdef _WIN32
#include<windows.h>

KrnlnApi bool 置磁盘卷标(const std::wstring& drive, const std::wstring& label) {
	std::wstring dir_name;
	if (drive.empty()) {
		wchar_t current_dir[MAX_PATH] = { 0 };
		if (GetCurrentDirectoryW(MAX_PATH, current_dir) == 0) {
			return false;
		}
		dir_name = current_dir;
	}
	else {
		dir_name = drive;
		dir_name += L":\\";
	}
	return SetVolumeLabelW(dir_name.c_str(), label.c_str());
}
KrnlnApi bool 置磁盘卷标(const std::string& drive, const std::string& label) {
	std::string dir_name;

	if (drive.empty()) {
		char current_dir[MAX_PATH] = { 0 };
		if (GetCurrentDirectoryA(MAX_PATH, current_dir) == 0) {
			return false;
		}
		dir_name = current_dir;
	}
	else {
		dir_name = drive;
		dir_name += ":\\";
	}

	return SetVolumeLabelA(dir_name.c_str(), label.c_str());
}


KrnlnApi bool 置磁盘卷标(char 磁盘驱动器字符, const std::string& 欲置入的卷标文本) {
	char DirName[4] = { 磁盘驱动器字符 ,':','\\','\0' };
	return SetVolumeLabelA(DirName, 欲置入的卷标文本.c_str());
}
KrnlnApi bool 置磁盘卷标(wchar_t 磁盘驱动器字符, const std::wstring& 欲置入的卷标文本) {
	wchar_t DirName[4] = { 磁盘驱动器字符 ,L':',L'\\',L'\0' };;
	return SetVolumeLabelW(DirName, 欲置入的卷标文本.c_str());
}

#endif // _WIN32
