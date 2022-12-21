#include<string>
#ifdef _WIN32
#include<windows.h>
std::string GetDiskLabel(const std::string& drive) {
	std::string dir_name;

	if (drive.empty()) {
		char current_dir[MAX_PATH];
		if (GetCurrentDirectoryA(MAX_PATH, current_dir) == 0) {
			return "";
		}
		dir_name = current_dir;
		dir_name[3] = 0;
	}
	else {
		dir_name = drive;
		dir_name += ":\\";
	}

	char volume[MAX_PATH];
	char file_system_name[64];
	DWORD volume_serial_number;
	if (GetVolumeInformationA(dir_name.c_str(), volume, MAX_PATH, &volume_serial_number, NULL, NULL, file_system_name, 64)) {
		return std::string(volume);
	}

	return "";
}

std::wstring GetDiskLabel(const std::wstring& drive) {
	std::wstring dir_name;

	if (drive.empty()) {
		wchar_t current_dir[MAX_PATH];
		if (GetCurrentDirectoryW(MAX_PATH, current_dir) == 0) {
			return L"";
		}
		dir_name = current_dir;
		dir_name[3] = 0;
	}
	else {
		dir_name = drive;
		dir_name += L":\\";
	}

	wchar_t volume[MAX_PATH];
	wchar_t file_system_name[64];
	DWORD volume_serial_number;
	if (GetVolumeInformationW(dir_name.c_str(), volume, MAX_PATH, &volume_serial_number, NULL, NULL, file_system_name, 64)) {
		return std::wstring(volume);
	}

	return L"";
}

KrnlnApi std::string 取磁盘卷标A(const std::string& 磁盘驱动器字符) {
	return GetDiskLabel(磁盘驱动器字符);
}

KrnlnApi std::wstring 取磁盘卷标W(const std::wstring& 磁盘驱动器字符) {

	return GetDiskLabel(磁盘驱动器字符);
}

KrnlnApi std::string 取磁盘卷标A(char 磁盘驱动器字符) {
	return GetDiskLabel(std::string(磁盘驱动器字符, 1));
}

KrnlnApi std::wstring 取磁盘卷标W(wchar_t 磁盘驱动器字符) {

	return GetDiskLabel(std::wstring(磁盘驱动器字符, 1));

}
#endif // _WIN32