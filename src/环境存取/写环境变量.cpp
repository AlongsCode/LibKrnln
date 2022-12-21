#include"string"



#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi bool 写环境变量(const string& 环境变量名称, const string& 欲写入内容)
{
	return SetEnvironmentVariableA(环境变量名称.c_str(), 欲写入内容.c_str()) == TRUE;
}

KrnlnApi bool 写环境变量(const wstring& 环境变量名称, const wstring& 欲写入内容)
{
	return SetEnvironmentVariableW(环境变量名称.c_str(), 欲写入内容.c_str()) == TRUE;
}
#else
/*linux*/
KrnlnApi bool 写环境变量(string 环境变量名称, string 欲写入内容)
{
	return _putenv_s(环境变量名称.c_str(), 欲写入内容.c_str()) == 0;
}
KrnlnApi bool 写环境变量W(wstring 环境变量名称, wstring 欲写入内容)
{
	return _wputenv_s(环境变量名称.c_str(), 欲写入内容.c_str()) == 0;
}
#endif


