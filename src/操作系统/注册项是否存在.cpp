#ifdef _WIN32
#pragma warning(disable:4996)
#include <Windows.h>
#include <string>

enum class 注册表根目录
{
	根类 = 1,
	现行设置,
	现行用户,
	本地机器,
	所有用户
};
//此处inlie并不是内联，而是防止函数重定义.
inline HKEY GetRegRootVal(注册表根目录 rootDirectory)
{
	switch (rootDirectory)
	{
	case 注册表根目录::根类:
		return HKEY_CLASSES_ROOT;
	case 注册表根目录::现行设置:
		return HKEY_CURRENT_CONFIG;
	case 注册表根目录::现行用户:
		return HKEY_CURRENT_USER;
	case 注册表根目录::本地机器:
		return HKEY_LOCAL_MACHINE;
	case 注册表根目录::所有用户:
		return HKEY_USERS;
	}

	return nullptr;
}

KrnlnApi bool 注册项是否存在(注册表根目录 rootDirectory, const std::string& fullPathKeyName)
{
	const HKEY hRootKey = GetRegRootVal(rootDirectory);
	if (hRootKey == nullptr)
	{
		return false;
	}

	const size_t keyNameLength = fullPathKeyName.size();
	if (keyNameLength == 0)
	{
		return false;
	}

	char* pSubkey = new char[keyNameLength + 1];
	strcpy(pSubkey, fullPathKeyName.c_str());
	char* pKeyName = strrchr(pSubkey, '\\');
	if (pKeyName != nullptr)
	{
		*pKeyName = '\0';
		pKeyName++;
	}
	HKEY hKey;
	const LONG openKeyResult = RegOpenKeyA(hRootKey, pSubkey, &hKey);
	delete[] pSubkey;

	if (openKeyResult != ERROR_SUCCESS)
	{
		return false;
	}
	DWORD valueNameLength = MAX_PATH;
	DWORD valueType;
	char value[MAX_PATH];
	const LONG queryValueResult = RegQueryValueExA(hKey, pKeyName, nullptr, &valueType, reinterpret_cast<LPBYTE>(value), &valueNameLength);
	RegCloseKey(hKey);
	return queryValueResult == ERROR_SUCCESS || queryValueResult == ERROR_MORE_DATA;
}


KrnlnApi bool 注册项是否存在(注册表根目录 rootDirectory, const std::wstring& fullPathKeyName)
{
	const HKEY hRootKey = GetRegRootVal(rootDirectory);
	if (hRootKey == nullptr)
	{
		return false;
	}
	const size_t keyNameLength = fullPathKeyName.size();
	if (keyNameLength == 0)
	{
		return false;
	}

	wchar_t* pSubkey = new wchar_t[keyNameLength + 1];
	wcscpy(pSubkey, fullPathKeyName.c_str());
	wchar_t* pKeyName = wcsrchr(pSubkey, L'\\');
	if (pKeyName != nullptr)
	{
		*pKeyName = L'\0';
		pKeyName++;
	}
	HKEY hKey;
	const LONG openKeyResult = RegOpenKeyW(hRootKey, pSubkey, &hKey);
	delete[] pSubkey;

	if (openKeyResult != ERROR_SUCCESS)
	{
		return false;
	}
	DWORD valueNameLength = MAX_PATH;
	DWORD valueType;
	wchar_t value[MAX_PATH];
	const LONG queryValueResult = RegQueryValueExW(hKey, pKeyName, nullptr, &valueType, reinterpret_cast<LPBYTE>(value), &valueNameLength);
	RegCloseKey(hKey);
	return queryValueResult == ERROR_SUCCESS || queryValueResult == ERROR_MORE_DATA;
}
#endif