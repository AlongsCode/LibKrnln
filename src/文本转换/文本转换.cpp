#include <string>

//#pragma comment(lib, "comctl32.lib")
#ifdef _WIN32//winapi和速度库差距较大，win下用winapi
#include<windows.h>
KrnlnApi std::string 宽文本到文本(const std::wstring& 宽文本)
{
	int asciisize = ::WideCharToMultiByte(CP_ACP, 0, 宽文本.c_str(), -1, NULL, 0, NULL, NULL);
	if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (asciisize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	char* resultstring = new char[asciisize];

	int convresult = ::WideCharToMultiByte(CP_ACP, 0, 宽文本.c_str(), -1, resultstring, asciisize, NULL, NULL);
	if (convresult != asciisize)
	{
		throw std::exception("La falla!");
	}
	std::string Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
KrnlnApi std::wstring 文本到宽文本(const std::string& 文本)
{
	int widesize = MultiByteToWideChar(CP_ACP, 0, 文本.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	wchar_t* resultstring = new wchar_t[widesize];

	int convresult = MultiByteToWideChar(CP_ACP, 0, 文本.c_str(), -1, resultstring, widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	std::wstring wstrReturn(resultstring);
	delete[] resultstring;
	return wstrReturn;
}
KrnlnApi std::wstring UTF8到宽文本(const char* lpcszString)
{
	size_t len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[(size_t)unicodeLen + 1];
	memset((void*)pUnicode, 0, ((size_t)unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}
KrnlnApi std::wstring UTF8到宽文本(const std::string& utf8string)
{
	int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
	if (widesize == ERROR_NO_UNICODE_TRANSLATION)
	{
		throw std::exception("Invalid UTF-8 sequence.");
	}
	if (widesize == 0)
	{
		throw std::exception("Error in conversion.");
	}
	wchar_t* resultstring = new wchar_t[widesize];
	int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
	if (convresult != widesize)
	{
		throw std::exception("La falla!");
	}
	std::wstring Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
KrnlnApi std::string 宽文本到UTF8(const std::wstring& widestring)
{
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	char* resultstring = new char[utf8size];
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, resultstring, utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	std::string Ret(resultstring);
	delete[]resultstring;
	return Ret;
}
#else
#include <locale.h>
KrnlnApi std::wstring UTF8到宽文本(const std::string& lpcszString)
{
	size_t len = lpcszString.size();
	size_t unicodeLen = mbstowcs(NULL, lpcszString.c_str(), len) + 1;
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen];
	memset((void*)pUnicode, 0, (unicodeLen) * sizeof(wchar_t));
	mbstowcs(pUnicode, lpcszString.c_str(), len);
	std::wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}
KrnlnApi std::string 宽文本到UTF8(const std::wstring& widestring)
{
	if (widestring.empty())
	{
		return {};
	}
	size_t utf8size = wcstombs(NULL, widestring.c_str(), 0) + 1;
	char* utf8string = new char[utf8size];
	wcstombs(utf8string, widestring.c_str(), utf8size);
	std::string utf8str(utf8string);
	delete[] utf8string;
	return utf8str;
}
KrnlnApi std::string 宽文本到文本(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char* _Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
KrnlnApi std::wstring UTF8到宽文本(const char* lpcszString)
{
	size_t len = strlen(lpcszString);
	int unicodeLen = mbstowcs(NULL, lpcszString, len);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[(size_t)unicodeLen + 1];
	memset((void*)pUnicode, 0, ((size_t)unicodeLen + 1) * sizeof(wchar_t));
	mbstowcs(pUnicode, lpcszString, len);
	std::wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}

KrnlnApi std::wstring 文本到宽文本(const std::string& s)
{
	setlocale(LC_ALL, "chs");

	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t* _Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;

	setlocale(LC_ALL, "C");

	return result;
}

#endif // _WIN32
KrnlnApi std::string 文本到UTF8(const std::string& 文本)
{
	return 宽文本到UTF8(文本到宽文本(文本));
}


