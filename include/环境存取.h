#pragma once
#ifdef _WIN32
std::vector<std::wstring> 枚举注册表项(HKEY 根类, const std::wstring& 父路径);
std::vector<std::string> 枚举注册表项(HKEY 根类, const std::string& 父路径);
std::vector<std::wstring> 取命令行W();
std::vector<std::string> 取命令行A();

size_t 取命令行W(std::vector<std::wstring>& saryArgs);
size_t 取命令行A(std::vector<std::string>& saryArgs);
#ifdef _UNICODE
#define  取命令行  取命令行W
#else
#define  取命令行  取命令行A
#endif


#endif
#ifdef _UNICODE
#define 取运行目录 取运行目录W
#define 取执行文件名 取执行文件名W
#else
#define 取运行目录 取运行目录A
#define 取执行文件名 取执行文件名A
#endif


std::string 取执行文件名A();
std::wstring 取执行文件名W();

std::string 读环境变量(const std::string& 环境变量名称);
std::wstring 读环境变量(const std::wstring& 环境变量名称);



//将目录中所有的"/"转为"\",所有的大写转小写
std::string 规范化路径(const std::string& 路径);
//将目录中所有的"/"转为"\",所有的大写转小写
std::wstring 规范化路径(const std::wstring& 路径);
std::wstring 取运行目录W();
std::string 取运行目录A();

bool 写环境变量(const std::string& 环境变量名称, const std::string& 欲写入内容);
bool 写环境变量(const std::wstring& 环境变量名称, const std::wstring& 欲写入内容);




/*目录为空则取当前路径*/
std::string 合并路径(const std::string& 文件名, const std::string& 目录 = "");
/*目录为空则取当前路径*/
std::wstring 合并路径(const std::wstring& 文件名, const std::wstring& 目录 = L"");