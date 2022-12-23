#ifdef _WIN32
#pragma warning(disable:4996)
#include <Windows.h>
#include <string>
#include<vector>

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

KrnlnApi bool 写注册项(注册表根目录 rootDirectory, const std::string& fullPathKeyName, const std::string& value)
{
	DWORD dwLen = 0;
	DWORD dwType;
	LPBYTE pData = NULL;


	dwType = REG_SZ;
	if (!value.empty())
	{
		dwLen = (DWORD)value.size() + 1;
		pData = LPBYTE(value.c_str());
	}



	HKEY hRootkey = GetRegRootVal(rootDirectory);
	BOOL bRet = FALSE;
	size_t nLen = fullPathKeyName.size();
	if (hRootkey && nLen)
	{
		HKEY hkey;
		char* pSubkey = new char[nLen + 1];
		strcpy(pSubkey, fullPathKeyName.c_str());
		char* pKeyname = strrchr(pSubkey, '\\');
		if (pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if (RegCreateKeyExA(hRootkey, pSubkey, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS)
		{
			if (RegSetValueExA(hkey, pKeyname, 0, dwType, pData, dwLen) == ERROR_SUCCESS)
			{
				bRet = TRUE;
			}

			RegCloseKey(hkey);
		}
		delete[] pSubkey;
	}

	return bRet;
}



KrnlnApi bool 写注册项(注册表根目录 rootDirectory, const std::string& fullPathKeyName, const std::vector<unsigned char>& value)
{
	DWORD dwLen = 0;
	DWORD dwType;
	LPBYTE pData = NULL;

	//字节集
	dwType = REG_BINARY;
	if (!value.empty())
	{
		dwLen = (DWORD)value.size();
		pData = const_cast<LPBYTE>(value.data());
	}
	HKEY hRootkey = GetRegRootVal(rootDirectory);
	BOOL bRet = FALSE;
	size_t nLen = fullPathKeyName.size();
	if (hRootkey && nLen)
	{
		HKEY hkey;
		char* pSubkey = new char[nLen + 1];
		strcpy(pSubkey, fullPathKeyName.c_str());
		char* pKeyname = strrchr(pSubkey, '\\');
		if (pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if (RegCreateKeyExA(hRootkey, pSubkey, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS)
		{
			if (RegSetValueExA(hkey, pKeyname, 0, dwType, pData, dwLen) == ERROR_SUCCESS)
			{
				bRet = TRUE;
			}

			RegCloseKey(hkey);
		}
		delete[] pSubkey;
	}

	return bRet;
}

KrnlnApi bool 写注册项(注册表根目录 rootDirectory, const std::wstring& fullPathKeyName, const std::wstring& value)
{
	DWORD dwLen = 0;
	DWORD dwType;
	LPBYTE pData = NULL;
	dwType = REG_SZ;
	if (!value.empty())
	{
		dwLen = (DWORD)value.size() + 1;
		pData = LPBYTE(value.c_str());
	}



	HKEY hRootkey = GetRegRootVal(rootDirectory);
	BOOL bRet = FALSE;
	size_t nLen = fullPathKeyName.size();
	if (hRootkey && nLen)
	{
		HKEY hkey;
		wchar_t* pSubkey = new wchar_t[nLen + 1];
		wcscpy(pSubkey, fullPathKeyName.c_str());
		wchar_t* pKeyname = wcsrchr(pSubkey, L'\\');
		if (pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if (RegCreateKeyExW(hRootkey, pSubkey, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS)
		{
			if (RegSetValueExW(hkey, pKeyname, 0, dwType, pData, dwLen) == ERROR_SUCCESS)
			{
				bRet = TRUE;
			}

			RegCloseKey(hkey);
		}
		delete[] pSubkey;
	}

	return bRet;
}

KrnlnApi bool 写注册项(注册表根目录 rootDirectory, const std::wstring& fullPathKeyName, const std::vector<unsigned char>& value)
{
	DWORD dwLen = 0;
	DWORD dwType;
	LPBYTE pData = NULL;
	//字节集
	dwType = REG_BINARY;
	if (!value.empty())
	{
		dwLen = (DWORD)value.size();
		pData = const_cast<LPBYTE>(value.data());
	}
	HKEY hRootkey = GetRegRootVal(rootDirectory);
	BOOL bRet = FALSE;
	size_t nLen = fullPathKeyName.size();
	if (hRootkey && nLen)
	{
		HKEY hkey;
		wchar_t* pSubkey = new wchar_t[nLen + 1];
		wcscpy(pSubkey, fullPathKeyName.c_str());
		wchar_t* pKeyname = wcsrchr(pSubkey, L'\\');
		if (pKeyname)
		{
			*pKeyname = 0;
			pKeyname++;
		}
		if (RegCreateKeyExW(hRootkey, pSubkey, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS)
		{
			if (RegSetValueExW(hkey, pKeyname, 0, dwType, pData, dwLen) == ERROR_SUCCESS)
			{
				bRet = TRUE;
			}

			RegCloseKey(hkey);
		}
		delete[] pSubkey;
	}

	return bRet;
}


//模板换位重载
//template<typename T>
//bool WriteRegistryKey(注册表根目录 rootDirectory, const std::string& fullPathKeyName, const T& value)
//{
//	DWORD dwLen = 0;
//	DWORD dwType;
//	LPBYTE pData = NULL;
//
//	//字节集
//	if constexpr (std::is_same_v<T, std::vector<unsigned char>>)
//	{
//		dwType = REG_BINARY;
//		if (!value.empty())
//		{
//			dwLen = value.size();
//			pData = value.data();
//		}
//	}
//	//文本
//	else if constexpr (std::is_same_v<T, std::string>)
//	{
//		dwType = REG_SZ;
//		if (!value.empty())
//		{
//			dwLen = value.size() + 1;
//			pData = reinterpret_cast<LPBYTE>(&value[0]);
//		}
//	}
//	else
//	{
//		return 0;
//	}
//
//	HKEY hRootkey = GetRegRootVal(rootDirectory);
//	BOOL bRet = FALSE;
//	size_t nLen = fullPathKeyName.size();
//	if (hRootkey && nLen)
//	{
//		HKEY hkey;
//		char* pSubkey = new char[nLen + 1];
//		strcpy(pSubkey, fullPathKeyName.c_str());
//		char* pKeyname = strrchr(pSubkey, '\\');
//		if (pKeyname)
//		{
//			*pKeyname = 0;
//			pKeyname++;
//		}
//		if (RegCreateKeyExA(hRootkey, pSubkey, 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS)
//		{
//			if (RegSetValueExA(hkey, pKeyname, 0, dwType, pData, dwLen) == ERROR_SUCCESS)
//			{
//				bRet = TRUE;
//			}
//
//			RegCloseKey(hkey);
//		}
//		delete[] pSubkey;
//	}
//
//	return bRet;
//}
//
















#endif