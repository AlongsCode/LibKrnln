#ifdef _WIN32
#include <Windows.h>
#include <string>
#include<commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;
enum class 高级信息框按钮 {
	确认 = 1,
	是 = 2,
	否 = 4,
	取消 = 8,
	重试 = 16,
	关闭 = 32,
	失败 = 0
};
KrnlnApi 高级信息框按钮 operator| (高级信息框按钮 lhs, 高级信息框按钮 rhs)
{
	return static_cast<高级信息框按钮> (static_cast<int>(lhs) | static_cast<int>(rhs));
}
KrnlnApi 高级信息框按钮 高级信息框(const wstring& 信息, const wstring& 标题, const wstring& 窗口标题, 高级信息框按钮 按钮, HWND parent, int 图标)
{
	const PWSTR icon[] = { nullptr,TD_ERROR_ICON,TD_INFORMATION_ICON,TD_SHIELD_ICON,TD_WARNING_ICON , MAKEINTRESOURCEW(-8),MAKEINTRESOURCEW(-7) };
	TASKDIALOGCONFIG config = { sizeof(TASKDIALOGCONFIG) };
	config.hwndParent = parent;
	config.pszWindowTitle = 窗口标题.c_str();
	config.pszMainInstruction = 标题.c_str();
	config.pszContent = 信息.c_str();
	config.dwCommonButtons = static_cast<TASKDIALOG_COMMON_BUTTON_FLAGS>(按钮);
	if (图标 > 0 && 图标 <= 6)
	{
		config.pszMainIcon = icon[图标];
	}

	int buttonPressed;
	HRESULT hr = TaskDialogIndirect(&config, &buttonPressed, NULL, NULL);
	if (SUCCEEDED(hr))
	{
		switch (buttonPressed) {
		case IDOK:
			return 高级信息框按钮::确认;
		case IDCANCEL:
			return 高级信息框按钮::取消;
		case IDRETRY:
			return 高级信息框按钮::重试;
		case IDYES:
			return 高级信息框按钮::是;
		case IDNO:
			return 高级信息框按钮::否;
		case IDCLOSE:
			return 高级信息框按钮::关闭;
		default:
			break;
		}
	}
	return 高级信息框按钮::失败;
}



#endif