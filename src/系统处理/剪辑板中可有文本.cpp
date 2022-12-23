#include <string>

#ifdef _WIN32
#include <windows.h>
#else
//#include <X11/Xlib.h>
//#include <X11/Xatom.h>
#include <cstdio>
#endif

KrnlnApi bool 剪辑板可有文本()
{
#ifdef _WIN32
	// Windows version: use Win32 API
	BOOL bRet = FALSE;
	if (OpenClipboard(NULL))
	{
		HANDLE hClip = GetClipboardData(CF_TEXT);
		if (hClip)
			bRet = TRUE;
		CloseClipboard();
	}
	return bRet;
#else
	// Non-Windows version: use popen to execute "xclip -o -selection clipboard"
	std::string command = "xclip -o -selection clipboard";
	FILE* fp = popen(command.c_str(), "r");
	if (fp == nullptr)
		return false;
	int c = fgetc(fp);
	int ret = pclose(fp);
	return c != EOF || ret == 0;

#endif
}