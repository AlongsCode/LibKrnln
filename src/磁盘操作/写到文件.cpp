#pragma warning(disable:4996)
#include<string>
#include<vector>
using namespace std; //直接使用标准库输出差距不大
//#ifdef _WIN32
//#include<windows.h>
//
//
//KrnlnApi bool 写到文件(string 文件名, vector<unsigned char> 欲写入文件的数据) {
//
//
//	HANDLE hFile = CreateFileA(文件名.c_str(),
//		GENERIC_WRITE,
//		0,
//		NULL,
//		CREATE_ALWAYS,
//		FILE_ATTRIBUTE_ARCHIVE,
//		0);
//
//	BOOL bRet = FALSE;
//	if (hFile != INVALID_HANDLE_VALUE)
//	{
//
//		DWORD dwNumOfByteRead;
//		bRet = TRUE;
//
//		LPBYTE pData = 欲写入文件的数据.data();
//		INT nLen = 欲写入文件的数据.size();
//
//		if (WriteFile(hFile, pData, nLen, &dwNumOfByteRead, NULL) == FALSE)
//		{
//			bRet = FALSE;
//		}
//		/*			if(FlushFileBuffers(hFile)==FALSE)
//					{
//						bRet = FALSE;
//						break;
//					}*/
//
//		CloseHandle(hFile);
//	}
//	return bRet;
//
//
//}
//
//KrnlnApi bool 写到文件(wstring 文件名, vector<unsigned char>  欲写入文件的数据) {
//
//
//	HANDLE hFile = CreateFileW(文件名.c_str(),
//		GENERIC_WRITE,
//		0,
//		NULL,
//		CREATE_ALWAYS,
//		FILE_ATTRIBUTE_ARCHIVE,
//		0);
//
//	BOOL bRet = FALSE;
//	if (hFile != INVALID_HANDLE_VALUE)
//	{
//
//		DWORD dwNumOfByteRead;
//		bRet = TRUE;
//
//		LPBYTE pData = 欲写入文件的数据.data();
//		INT nLen = 欲写入文件的数据.size();
//
//		if (WriteFile(hFile, pData, nLen, &dwNumOfByteRead, NULL) == FALSE)
//		{
//			bRet = FALSE;
//		}
//		/*			if(FlushFileBuffers(hFile)==FALSE)
//					{
//						bRet = FALSE;
//						break;
//					}*/
//
//		CloseHandle(hFile);
//	}
//	return bRet;
//
//
//}
//
//#else
//
//#endif



KrnlnApi bool 写到文件(const wstring& 文件名, vector<unsigned char> 欲写入文件的数据)
{

	if (文件名.empty() || 欲写入文件的数据.empty())
		return false;

	FILE* out = _wfopen(文件名.c_str(), L"wb");
	if (out == NULL)
		return false;

	const bool blpSucceeded = (fwrite(欲写入文件的数据.data(), 1, 欲写入文件的数据.size(), out) == 欲写入文件的数据.size());
	fclose(out);
	return blpSucceeded;
}
KrnlnApi bool 写到文件(const string& 文件名, vector<unsigned char> 欲写入文件的数据)
{

	if (文件名.empty() || 欲写入文件的数据.empty())
		return false;

	FILE* out = fopen(文件名.c_str(), "wb");
	if (out == NULL)
		return false;

	const bool blpSucceeded = (fwrite(欲写入文件的数据.data(), 1, 欲写入文件的数据.size(), out) == 欲写入文件的数据.size());
	fclose(out);
	return blpSucceeded;
}