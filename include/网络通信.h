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



std::vector<unsigned char>
网页访问(
	const std::string& n_url,//0
	int  n_access_method,//1
	const std::string& n_post_data,//2
	const std::string& n_post_Cookies,//3
	std::string* pRetCookies,//4
	const std::string& n_add_itional_header,//5
	std::string* pRetHead,//6
	const std::optional<BOOL> n_no_redirect,//7
	std::vector<unsigned char>  n_post_data_pBuffer,//8
	const std::string& n_pox_addr,//9
	const std::optional<BOOL>  n_is_completion_head,//10
	const std::optional<BOOL>  n_is_make_head_up,//11
	const std::optional<BOOL>  n_is_socks4//12
);

#endif // _WIN32


