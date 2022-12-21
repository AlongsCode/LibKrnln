
#include<vector>
#include<filesystem>


using namespace std;
inline int MyStrcmp(const wchar_t* szSource, const wchar_t* szDest)
{
	if (szSource == NULL)  szSource = L"";
	if (szDest == NULL)  szDest = L"";

	int nResult = 0;
	while (!(nResult = (int)(*szSource - *szDest)) && *szDest)
	{
		szSource++;
		szDest++;
	}

	return nResult;
}
inline int MyStrcmp(const char* szSource, const char* szDest)
{
	if (szSource == NULL)  szSource = "";
	if (szDest == NULL)  szDest = "";

	int nResult = 0;
	while (!(nResult = (int)(*szSource - *szDest)) && *szDest)
	{
		szSource++;
		szDest++;
	}

	return nResult;
}
KrnlnApi wstring 合并路径(const wstring& 文件名, const wstring& 目录)
{
	// 取当前目录
	wstring strCurrentDir;
	if (目录.empty())
	{
		strCurrentDir = std::filesystem::current_path().wstring();
	}
	else
	{
		strCurrentDir = 目录;
	}

	// 按'/'或'\\'分割
	vector<wstring> tokens;

	wstring strPath = strCurrentDir;
	strPath += L"/";
	strPath += 文件名;
	const wchar_t* szPrevToken = strPath.c_str();
	for (const wchar_t* p = szPrevToken; *p; ++p)
	{
		if (*p == L'\\' || *p == L'/')
		{
			tokens.push_back(wstring(szPrevToken, p - szPrevToken));
			szPrevToken = p + 1;
		}
	}
	if (*szPrevToken)
	{
		tokens.push_back(szPrevToken);
	}

	// 处理 "." 和 ".."
	vector<wstring>  tempArray;
	for (size_t n = 0; n < tokens.size(); ++n)
	{
		wstring szTok = tokens[n];
		if (szTok.empty()) {
			continue;
		}
		else if (MyStrcmp(L".", szTok.c_str()) == 0) {
			continue;
		}
		else if (MyStrcmp(L"..", szTok.c_str()) == 0)
		{
			size_t nTempArrayCount = tempArray.size();
			if (nTempArrayCount > 1)
			{
				tempArray.pop_back();
			}
		}
		else
		{
			tempArray.push_back(szTok);
		}
	}
	// 生成最终文本
	size_t nCount = tempArray.size();
	wstring strReturn;
	for (size_t n2 = 0; n2 < nCount; ++n2)
	{
		strReturn += tempArray[n2];
		if (n2 != nCount - 1)
		{
			strReturn += L"/";
		}
	}
	return strReturn;
}

KrnlnApi string 合并路径(const string& 文件名, const string& 目录)
{
	// 取当前目录
	string strCurrentDir;
	if (目录.empty())
	{
		strCurrentDir = std::filesystem::current_path().string();

	}
	else
	{
		strCurrentDir = 目录;
	}

	// 按'/'或'\\'分割
	vector<string> tokens;

	string strPath = strCurrentDir;
	strPath += "/";
	strPath += 文件名;
	const char* szPrevToken = strPath.c_str();
	for (const char* p = szPrevToken; *p; ++p)
	{
		if (*p == L'\\' || *p == L'/')
		{
			tokens.push_back(string(szPrevToken, p - szPrevToken));
			szPrevToken = p + 1;
		}
	}
	if (*szPrevToken)
	{
		tokens.push_back(szPrevToken);
	}

	// 处理 "." 和 ".."
	vector<string>  tempArray;
	for (size_t n = 0; n < tokens.size(); ++n)
	{
		string szTok = tokens[n];
		if (szTok.empty())
			continue;
		else if (MyStrcmp(".", szTok.c_str()) == 0)
			continue;
		else if (MyStrcmp("..", szTok.c_str()) == 0)
		{
			size_t nTempArrayCount = tempArray.size();
			if (nTempArrayCount > 1)
			{
				tempArray.pop_back();
			}
		}
		else
		{
			tempArray.push_back(szTok);
		}
	}

	// 生成最终文本
	size_t nCount = tempArray.size();
	string strReturn;
	for (size_t n2 = 0; n2 < nCount; ++n2)
	{
		strReturn += tempArray[n2];
		if (n2 != nCount - 1)
		{
			strReturn += "/";
		}
	}

	return strReturn;

}