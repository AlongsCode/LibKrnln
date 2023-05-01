#include<string>
#include<windows.h>
#include <shlobj.h>
/*此参数表示要获取的特殊文件夹的类型。
值为1时表示获取我的文档文件夹路径；
值为2时表示获取我的收藏夹路径；
值为3时表示获取桌面文件夹路径；
值为4时表示获取字体文件夹路径；
值为5时表示获取开始菜单文件夹路径；
值为6时表示获取程序文件夹路径；
值为7时表示获取启动文件夹路径；
值为8时表示获取应用程序数据文件夹路径；
值为9时表示获取Windows文件夹路径；
值为10时表示获取系统文件夹路径；
值为11时表示获取临时文件夹路径。
值为12时表示获取program文件夹。
*/
KrnlnApi std::wstring 取特定目录(DWORD Type) {
	wchar_t path[MAX_PATH + 1] = { 0 };
	BOOL IsSucceeded = FALSE;
	if (Type >= 1 && Type <= 8) {
		IsSucceeded = SHGetSpecialFolderPathW(NULL, path, (Type == 1 ? CSIDL_PERSONAL : Type == 2 ? CSIDL_FAVORITES : Type == 3 ? CSIDL_DESKTOPDIRECTORY :
			Type == 4 ? CSIDL_FONTS : Type == 5 ? CSIDL_STARTMENU : Type == 6 ? CSIDL_PROGRAMS : Type == 7 ? CSIDL_STARTUP : Type == 12 ? CSIDL_PROGRAM_FILES : CSIDL_APPDATA), FALSE);
	}
	else if (Type == 9) {
		IsSucceeded = (GetWindowsDirectoryW(path, MAX_PATH) > 0);
	}
	else if (Type == 10) {
		IsSucceeded = (GetSystemDirectoryW(path, MAX_PATH) > 0);
	}
	else {
		if (Type != 11) {
			return {};
		}
		IsSucceeded = (GetTempPathW(MAX_PATH, path) > 0);
	}
	std::wstring Ret;
	if (IsSucceeded) {
		size_t lenth = wcslen(path);
		if (lenth > 0 && path[lenth - 1] != L'\\') {
			path[lenth] = L'\\';
			path[lenth + 1] = L'\0';
		}
		Ret = path;
	}
	return Ret;
};