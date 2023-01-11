#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <string>


/* 在标准输入设备上请求输入一行文本，返回用户所输入的内容。注意本命令只能在控制台程序中使用。
	参数<1>的名称为“是否回显”，类型为“逻辑型（bool）”，可以被省略,默认为真。本参数决定输入时是否显示所输入字符，为假不显示，为真显示。如果被省略，默认值为真，即回显。可以通过将本参数设置为假以输入密码等特殊信息。*/
KrnlnApi bool 置控制台标题(const std::string& title)
{
#ifdef _WIN32
	return SetConsoleTitleA(title.c_str());
#else
	std::string command = "title " + title;
	return !system(command.c_str());
#endif
}

KrnlnApi bool 置控制台标题(const std::wstring& title)
{
#ifdef _WIN32
	return SetConsoleTitleW(title.c_str());
#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	std::string command = "title " + conv.to_bytes(title);
	return !system(command.c_str());
#endif
}

