#ifdef _WIN32
#include <Windows.h>
#include <string>
using namespace std;
EXTERN_C{
	int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
	int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
}

KrnlnApi int 信息框(const wstring& 提示信息, int 按钮, const wstring& 窗口标题, HWND 父窗口, DWORD 留存时长) {
	const HWND hOldFocusWnd = ::GetFocus();
	INT nResult = 1;
	if (留存时长 > 0)
	{
		nResult = ::MessageBoxTimeoutW((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮, 0, 留存时长);
	}
	else
	{
		nResult = ::MessageBoxW((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮);
	}

	if (hOldFocusWnd != NULL && ::IsWindow(hOldFocusWnd)) {
		::SetFocus(hOldFocusWnd);
	}
	return nResult - 1;
}


KrnlnApi int 信息框(const string& 提示信息, int 按钮, const string& 窗口标题, HWND 父窗口, DWORD 留存时长) {
	const HWND hOldFocusWnd = ::GetFocus();
	INT nResult = 1;
	if (留存时长 > 0)
	{
		nResult = ::MessageBoxTimeoutA((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮, 0, 留存时长);
	}
	else
	{
		nResult = ::MessageBoxA((HWND)父窗口, 提示信息.c_str(), 窗口标题.c_str(), 按钮);
	}

	if (hOldFocusWnd != NULL && ::IsWindow(hOldFocusWnd)) {
		::SetFocus(hOldFocusWnd);
	}
	return nResult - 1;
}
#endif 


