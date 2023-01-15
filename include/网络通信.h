#pragma once
/*打开指定的url，或者是指定的文件夹*/
void 打开指定网址(const string& url);
/*打开指定的url，或者是指定的文件夹*/
void 打开指定网址(const wstring& url);


std::string 取本机名();



std::wstring 取本机IPW();

std::string 取本机IPA();

#ifdef _UNICODE
#define 取本机IP 取本机IPW
#else
#define 取本机IP 取本机IPA
#endif
#pragma endregion 
