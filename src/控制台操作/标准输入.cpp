#include<iostream>
#include <string>
#ifdef _WIN32
#include<conio.h>
#else
#include <unistd.h>
#endif // _WIN32


/* 在标准输入设备上请求输入一行文本，返回用户所输入的内容。注意本命令只能在控制台程序中使用。
	参数<1>的名称为“是否回显”，类型为“逻辑型（bool）”，可以被省略,默认为真。本参数决定输入时是否显示所输入字符，为假不显示，为真显示。如果被省略，默认值为真，即回显。可以通过将本参数设置为假以输入密码等特殊信息。*/
KrnlnApi std::string 标准输入A(bool 是否回显)
{
	std::string result;
	if (是否回显) {
		// 使用 std::getline 从标准输入流读取一行字符串
		std::getline(std::cin, result);
	}
	else {
#ifdef _WIN32
		char c;
		while ((c = (char)_getch()) != '\r' && c != '\0' && c != '\n') {
			result.push_back(c);
		}
#else
		char* c = getpass(nullptr);
		result = c ? c : "";
#endif // _WIN32

	}
	return result;
}

KrnlnApi std::wstring 标准输入W(bool 是否回显, std::string 编码格式)
{

	std::wcin.imbue(std::locale(编码格式));
	std::wstring result;
	if (是否回显) {
		// 使用 std::getline 从标准输入流读取一行字符串
		std::getline(std::wcin, result);
	}
	else {
#ifdef _WIN32
		wchar_t c;
		while ((c = (wchar_t)_getch()) != L'\r' && c != L'\0' && c != L'\n') {
			result.push_back(c);
		}
#else
		wchar_t* c = _wgetpass(nullptr);
		result = c ? c : L"";
#endif // _WIN32

	}
	return result;
}


