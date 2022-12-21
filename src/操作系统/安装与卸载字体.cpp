
#ifdef _WIN32
#include<string>
#include<shlobj_core.h>
#include<shlwapi.h>
#include<vector>
#pragma comment(lib,"shlwapi.lib")
using namespace std;
KrnlnApi HANDLE  安装字体(const vector<unsigned char>& FontData)
{
	DWORD dwFonts = 0;
	return AddFontMemResourceEx((void*)FontData.data(), (DWORD)FontData.size(), 0, &dwFonts);
}
KrnlnApi BOOL  安装字体(const std::string& 字体文件)
{
	char pszPath[MAX_PATH] = { 0 };
	BOOL result = FALSE;
	if (SHGetSpecialFolderPathA(0, pszPath, 20, 0))
	{
		if (PathFileExistsA(字体文件.c_str()))
		{
			string::size_type iPos = 字体文件.find_last_of('\\');
			string filename = 字体文件.substr(iPos, 字体文件.length() - iPos);
			filename = pszPath + filename;

			if (CopyFileA(字体文件.c_str(), filename.c_str(), TRUE))
			{
				BOOL Ret = AddFontResourceA(字体文件.c_str());

				result = Ret;
				if (Ret) {
					SendMessageA(HWND_BROADCAST, 0x1Du, 0, 0);
				}
			}
		}
	}
	return result;
}
KrnlnApi BOOL  安装字体(const std::wstring& 字体文件)
{
	wchar_t pszPath[MAX_PATH] = { 0 };
	BOOL result = FALSE;
	if (SHGetSpecialFolderPathW(0, pszPath, 20, 0))
	{

		if (PathFileExistsW(字体文件.c_str()))
		{
			wstring::size_type iPos = 字体文件.find_last_of('\\');
			wstring filename = 字体文件.substr(iPos, 字体文件.length() - iPos);
			filename = pszPath + filename;
			if (CopyFileW(字体文件.c_str(), filename.c_str(), TRUE))
			{

				BOOL Ret = AddFontResourceW(字体文件.c_str());
				result = Ret;
				if (Ret) {
					SendMessageW(HWND_BROADCAST, 0x1Du, 0, 0);
				}
			}
		}
	}
	return result;
}
KrnlnApi BOOL 卸载字体(HANDLE 字体句柄)
{

	return RemoveFontMemResourceEx(字体句柄);
}
KrnlnApi BOOL 卸载字体(const string& lpFileName)
{
	BOOL Ret = FALSE;

	Ret = RemoveFontResourceA(lpFileName.c_str());
	if (Ret)
		SendMessageA(HWND_BROADCAST, 0x1Du, 0, 0);
	return Ret;
}
KrnlnApi bool 卸载字体(const std::wstring& lpFileName)
{
	BOOL Ret = FALSE;

	Ret = RemoveFontResourceW(lpFileName.c_str());
	if (Ret)
		SendMessageW(HWND_BROADCAST, 0x1Du, 0, 0);
	return Ret;
}
#endif 




