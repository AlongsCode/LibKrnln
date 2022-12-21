#include"string"
#include <algorithm>
using namespace std;
#pragma warning(disable:4996)//不加也行，看着烦得慌

inline bool text_isend(const char* szTest, const char* szEndOf)
{
	const size_t npTestStrLen = strlen(szTest);
	const size_t npEndStrLen = strlen(szEndOf);
	return (npEndStrLen == 0 || (npTestStrLen >= npEndStrLen && strcmp(szTest + npTestStrLen - npEndStrLen, szEndOf) == 0));
}

inline bool text_isend(const wchar_t* szTest, const wchar_t* szEndOf)
{
	const size_t npTestStrLen = wcslen(szTest);
	const size_t npEndStrLen = wcslen(szEndOf);
	return (npEndStrLen == 0 || (npTestStrLen >= npEndStrLen && wcscmp(szTest + npTestStrLen - npEndStrLen, szEndOf) == 0));
}
inline bool text_isendn(const wchar_t* szTest, const wchar_t* szEndOf)
{
	const size_t npTestStrLen = wcslen(szTest);
	const size_t npEndStrLen = wcslen(szEndOf);
	return (npEndStrLen == 0 || (npTestStrLen >= npEndStrLen && wcsicmp(szTest + npTestStrLen - npEndStrLen, szEndOf) == 0));
}
inline bool text_isendn(const char* szTest, const char* szEndOf)
{
	const size_t npTestStrLen = strlen(szTest);
	const size_t npEndStrLen = strlen(szEndOf);
	return (npEndStrLen == 0 || (npTestStrLen >= npEndStrLen && stricmp(szTest + npTestStrLen - npEndStrLen, szEndOf) == 0));
}

KrnlnApi bool 是否以文本结尾(const wstring& 所欲操作的文本, const wstring& 搜索字符, bool 是否区分大小写)
{
	if (!是否区分大小写)
	{
		return text_isendn(所欲操作的文本.c_str(), 搜索字符.c_str());
	}
	return text_isend(所欲操作的文本.c_str(), 搜索字符.c_str());
}
KrnlnApi bool 是否以文本结尾(const string& 所欲操作的文本, const string& 搜索字符, bool 是否区分大小写)
{
	if (!是否区分大小写)
	{
		return text_isendn(所欲操作的文本.c_str(), 搜索字符.c_str());
	}
	return text_isend(所欲操作的文本.c_str(), 搜索字符.c_str());
}