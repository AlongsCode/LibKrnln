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



inline std::string 读配置项(const std::string& 配置文件名, const std::string& 节名称, const std::string& 配置项名称, const std::string& 默认文本) {
	std::string pBuffer;
	DWORD nLen = 1024;
	do {
		pBuffer.resize(nLen + 1);
		DWORD nRet = GetPrivateProfileStringA(节名称.c_str(), 配置项名称.c_str(), 默认文本.c_str(), pBuffer.data(), nLen, 配置文件名.c_str());
		if (nRet < nLen - 1) {
			break;
		}
		nLen = nRet + 1024;
	} while (true);

	return pBuffer.c_str();
}

inline std::wstring 读配置项(const std::wstring& 配置文件名, const std::wstring& 节名称, const std::wstring& 配置项名称, const std::wstring& 默认文本) {
	std::wstring pBuffer;
	DWORD nLen = 1024;
	do {
		pBuffer.resize(nLen + 1);
		DWORD nRet = GetPrivateProfileStringW(节名称.c_str(), 配置项名称.c_str(), 默认文本.c_str(), pBuffer.data(), nLen, 配置文件名.c_str());

		if (nRet < nLen - 1) {
			break;
		}
		nLen = nRet + 1024;
	} while (true);
	return pBuffer.c_str();
}


/*此参数表示要获取的特殊文件夹的类型。
值为1时表示获取我的文档文件夹路径；
值为2时表示获取我的收藏夹路径；
值为3时表示获取桌面文件夹路径；
值为4时表示获取字体文件夹路径；
值为5时表示获取开始菜单文件夹路径；
值为6时表示获取程序文件夹路径；
值为7时表示获取启动文件夹路径；
值为8时表示获取应用程序数据文件夹路径；
值为9时表示获取Windows文件夹路径；
值为10时表示获取系统文件夹路径；
值为11时表示获取临时文件夹路径。
值为12时表示获取program文件夹。
*/
std::wstring 取特定目录(DWORD Type);
