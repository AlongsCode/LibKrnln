#include"string"
using namespace std;

#pragma warning(disable:4996)//不加也行，看着烦得慌

inline bool txet_isLeadOf(const char* szTest, const char* szLeadOf)
{
	return (strncmp(szTest, szLeadOf, strlen(szLeadOf)) == 0);
}
inline bool txet_isLeadOf(const wchar_t* szTest, const wchar_t* szLeadOf)
{
	return (wcsncmp(szTest, szLeadOf, wcslen(szLeadOf)) == 0);
}


inline bool txet_isnLeadOf(const char* szTest, const char* szLeadOf)
{
	return (strnicmp(szTest, szLeadOf, strlen(szLeadOf)) == 0);
}
inline bool txet_isnLeadOf(const wchar_t* szTest, const wchar_t* szLeadOf)
{
	return (wcsnicmp(szTest, szLeadOf, wcslen(szLeadOf)) == 0);
}
KrnlnApi bool 是否以文本开头(const string& 所欲操作的文本, const string& 搜索字符, bool 是否区分大小写)
{
	if (!是否区分大小写)
	{
		return txet_isnLeadOf(所欲操作的文本.c_str(), 搜索字符.c_str());
	}
	return txet_isLeadOf(所欲操作的文本.c_str(), 搜索字符.c_str());
}
KrnlnApi bool 是否以文本开头(const  wstring& 所欲操作的文本, const  wstring& 搜索字符, bool 是否区分大小写)
{
	if (!是否区分大小写)
	{
		return txet_isnLeadOf(所欲操作的文本.c_str(), 搜索字符.c_str());
	}
	return txet_isLeadOf(所欲操作的文本.c_str(), 搜索字符.c_str());
}