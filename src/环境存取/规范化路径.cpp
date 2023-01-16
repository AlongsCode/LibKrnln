#include<string>
using namespace std;





KrnlnApi string 规范化路径(const string& szPath)
{
	if (szPath.empty())
	{
		return {};
	}
	char* str = new char[szPath.size() + 1];
	memset(str, 0, sizeof(char) * (szPath.size() + 1));

	strcpy_s(str, szPath.size(), szPath.c_str());

	for (char* p = str; *p != 0; ++p)
	{
		if (*p >= 'A' && *p <= 'Z')
			*p += ('a' - 'A');
		if (*p == '\\')
			*p = '/';
	}
	string	ret(str);
	delete[]str;
	return ret;
}
KrnlnApi wstring 规范化路径(const wstring& szPath)
{
	if (szPath.empty())
	{
		return {};
	}
	wchar_t* str = new wchar_t[szPath.size() + 1];
	memset(str, 0, sizeof(wchar_t) * (szPath.size() + 1));
	wcscpy_s(str, szPath.size(), szPath.c_str());
	for (wchar_t* p = str; *p != 0; ++p)
	{
		if (*p >= L'A' && *p <= L'Z') {
			*p += (L'a' - L'A');
		}
		if (*p == L'\\') {
			*p = L'/';
		}
	}
	wstring	ret(str);
	delete[]str;
	return ret;
}