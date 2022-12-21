#include"STRING"
using namespace std;
KrnlnApi bool 文本对比(string 文本1, string 文本2)
{
	int result = 0;
	size_t strsize = 文本1.size();
	const char* s1 = 文本1.c_str();
	const char* s2 = 文本2.c_str();
	if (strsize <= 文本2.size())
	{
		result = strncmp(s1, s2, strsize);
		return  result == 0;
	}
	return false;
}
KrnlnApi bool 文本对比(wstring 文本1, wstring 文本2)
{
	int result = 0;
	size_t strsize = 文本1.size();
	const wchar_t* s1 = 文本1.c_str();
	const wchar_t* s2 = 文本2.c_str();
	if (strsize <= 文本2.size())
	{
		result = wcsncmp(s1, s2, strsize);
		return  result == 0;
	}
	return false;
}