#include<string>


#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi bool 删除目录(const string& 欲删除的目录名称) {
	if (欲删除的目录名称.empty())
		return FALSE;
	size_t nLen = 欲删除的目录名称.size();
	if (nLen == 0)//防止删除当前目录的根目录"\*"
		return FALSE;
	if (nLen == 1 && 欲删除的目录名称 == "\\")//防止删除当前目录的根目录"\*"
		return FALSE;
	return RemoveDirectoryA(欲删除的目录名称.c_str());//删除空目录
}
KrnlnApi bool 删除目录(const wstring& 欲删除的目录名称) {
	if (欲删除的目录名称.empty())
		return FALSE;
	size_t nLen = 欲删除的目录名称.size();
	if (nLen == 0)//防止删除当前目录的根目录"\*"
		return FALSE;
	if (nLen == 1 && 欲删除的目录名称 == L"\\")//防止删除当前目录的根目录"\*"
		return FALSE;
	return RemoveDirectoryW(欲删除的目录名称.c_str());//删除空目录
}

#else
#include"direct.h"

KrnlnApi bool 删除目录(const string& 欲删除的目录名称) {
	if (欲删除的目录名称.empty())
		return FALSE;
	size_t nLen = 欲删除的目录名称.size();
	if (nLen == 0)//防止删除当前目录的根目录"\*"
		return FALSE;
	if (nLen == 1 && 欲删除的目录名称 == "\\")//防止删除当前目录的根目录"\*"
		return FALSE;

	return rmdir(欲删除的目录名称.c_str()) == 0;
}
KrnlnApi bool 删除目录(const wstring& 欲删除的目录名称) {
	if (欲删除的目录名称.empty())
		return FALSE;
	size_t nLen = 欲删除的目录名称.size();
	if (nLen == 0)//防止删除当前目录的根目录"\*"
		return FALSE;
	if (nLen == 1 && 欲删除的目录名称 == L"\\")//防止删除当前目录的根目录"\*"
		return FALSE;
	return _wrmdir(欲删除的目录名称.c_str()) == 0;
}
#endif