#ifdef _WIN32
#include <Windows.h>
#include <string>
using namespace std;
KrnlnApi int 信息框(const wstring& 提示信息, int 按钮, const wstring& 窗口标题, HWND 父窗口) {
	const HWND hOldFocusWnd = ::GetFocus();
	const INT nResult = ::MessageBox((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮);
	if (hOldFocusWnd != NULL && ::IsWindow(hOldFocusWnd)) {
		::SetFocus(hOldFocusWnd);
	}
	return (nResult - 1);
}


KrnlnApi int 信息框(const string& 提示信息, int 按钮, const string& 窗口标题, HWND 父窗口) {
	const HWND hOldFocusWnd = ::GetFocus();
	const INT nResult = ::MessageBoxA((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮);
	if (hOldFocusWnd != NULL && ::IsWindow(hOldFocusWnd)) {
		::SetFocus(hOldFocusWnd);
	}
	return (nResult - 1);
}
#endif 


