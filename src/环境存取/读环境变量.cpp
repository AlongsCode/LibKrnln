#include<string>


#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi string 读环境变量(const string& 环境变量名称) {
	char* pBuf = new char[MAX_PATH];
	UINT nRet = GetEnvironmentVariableA(环境变量名称.c_str(), pBuf, MAX_PATH);
	if (nRet > MAX_PATH)//缓冲区不够
	{
		delete[]pBuf;//释放再申请
		pBuf = new char[nRet];
		GetEnvironmentVariableA(环境变量名称.c_str(), pBuf, nRet);
	}
	string Ret(pBuf);
	delete[]pBuf;
	return Ret;
}
KrnlnApi wstring 读环境变量(const wstring& 环境变量名称) {
	wchar_t* pBuf = new wchar_t[MAX_PATH];
	UINT nRet = GetEnvironmentVariableW(环境变量名称.c_str(), pBuf, MAX_PATH);
	if (nRet > MAX_PATH)//缓冲区不够
	{
		delete[]pBuf;//释放再申请
		pBuf = new wchar_t[nRet];
		GetEnvironmentVariableW(环境变量名称.c_str(), pBuf, nRet);
	}
	wstring Ret(pBuf);
	delete[]pBuf;
	return Ret;
}
#else
KrnlnApi string 读环境变量(const string& 环境变量名称) {
	char* val = getenv(环境变量名称.c_str());
	return val ? val : string();
}
KrnlnApi wstring 读环境变量(const wstring& 环境变量名称) {
	wchar_t* val = _wgetenv(环境变量名称.c_str());
	return val ? val : wstring();
}
#endif