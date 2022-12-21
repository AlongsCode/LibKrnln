#ifdef _WIN32//注册表仅在win环境下可用
#include<windows.h>
#include<string>
#include<vector>
using namespace std;


KrnlnApi vector<string> 枚举注册表项(HKEY 根类, const string& 父路径)
{
	REGSAM Type;
	HKEY pHkey;
	SYSTEM_INFO INFO;
	std::vector<string> ret;
	pHkey = 0;
	GetNativeSystemInfo(&INFO);
	if (INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (Type = KEY_WOW64_32KEY | KEY_ALL_ACCESS, INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)) {

		Type = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
	}

	RegOpenKeyExA(根类, 父路径.c_str(), 1, Type, &pHkey);
	char name[MAX_PATH] = {};
	if (!RegEnumKeyA(pHkey, 0, name, MAX_PATH))
	{
		ret.push_back(name);
		if (!RegEnumKeyA(pHkey, 1, name, MAX_PATH))
		{
			DWORD i = 2;
			do {
				ret.push_back(name);
			} while (!RegEnumKeyA(pHkey, i++, name, MAX_PATH));
		}
		RegCloseKey(pHkey);
	}
	return ret;
}
KrnlnApi vector<wstring> 枚举注册表项(HKEY 根类, const wstring& 父路径)
{
	REGSAM Type;
	HKEY pHkey;
	SYSTEM_INFO INFO;
	std::vector<wstring> ret;
	pHkey = 0;
	GetNativeSystemInfo(&INFO);
	if (INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || (Type = KEY_WOW64_32KEY | KEY_ALL_ACCESS, INFO.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)) {

		Type = KEY_WOW64_64KEY | KEY_ALL_ACCESS;
	}
	RegOpenKeyExW(根类, 父路径.c_str(), 1, Type, &pHkey);
	wchar_t name[MAX_PATH] = {};
	if (!RegEnumKeyW(pHkey, 0, name, MAX_PATH))
	{
		ret.push_back(name);
		if (!RegEnumKeyW(pHkey, 1, name, MAX_PATH))
		{
			DWORD i = 2;
			do {
				ret.push_back(name);
			} while (!RegEnumKeyW(pHkey, i++, name, MAX_PATH));
		}
		RegCloseKey(pHkey);
	}
	return ret;
}
#endif // _WIN32

