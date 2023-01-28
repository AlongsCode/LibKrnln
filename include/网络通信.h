#pragma once
/*打开指定的url，或者是指定的文件夹*/
void 打开指定网址(const std::string& url);
/*打开指定的url，或者是指定的文件夹*/
void 打开指定网址(const std::wstring& url);


std::string 取本机名();



std::wstring 取本机IPW();

std::string 取本机IPA();

#ifdef _UNICODE
#define 取本机IP 取本机IPW
#else
#define 取本机IP 取本机IPA
#endif
#pragma endregion 

#ifdef _WIN32
bool 端口检测(unsigned short 端口, const std::string& ip地址 = 取本机IPA());
bool 端口检测(unsigned short 端口, const std::wstring& ip地址 = 取本机IPW());
bool 是否联网();
/*类似UDP，用于无需长期监听的短期微量信息发送*/
bool 发送网络信息(const std::string& IP, u_short 端口, const std::vector<unsigned char> 数据);
/*类似UDP，用于无需长期监听的短期微量信息发送*/
bool 发送网络信息(const std::wstring& IP, u_short 端口, const std::vector<unsigned char> 数据);
#endif // _WIN32


