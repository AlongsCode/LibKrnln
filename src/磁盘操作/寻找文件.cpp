
#pragma region 老版本，对于linux支持度不是特表高，而且是易自己定义的用法，windows里不如直接用FindNext


//#include"string"
//#include"windows.h"
//#include"vector"
//using namespace std;
//#include"..\..\KrnlnHead\Defdll.h"
//
///
//调用格式： 〈文本型〉 寻找文件 （［文本型 欲寻找的文件或目录名称］，［整数型 欲寻找文件的属性］） - 系统核心支持库->磁盘操作
//    英文名称：dir
//    返回一个文本，用以表示所找到的文件名或目录名，它必须与所要求的名称格式或文件属性相匹配。支持使用多字符 (*) 和单字符 (?) 通配符来指定多重文件。在某子程序中第一次调用本命令时，必须指定“欲寻找文件”参数，否则将返回空文本 (“”)。在第一次调用以后如果想得到其它匹配的文件名，再一次调用本命令，且不要提供欲寻找文件名参数。如果已没有合乎条件的文件，本命令会返回一个空文本。一旦返回值为空文本，要再次调用本命令时，就必须指定“欲寻找文件”参数。不必访问完所有当前匹配的文件名，就可以使用一个新的“欲寻找文件”进行新的寻找。本命令为初级命令。
//    参数<1>的名称为“欲寻找的文件或目录名称”，类型为“文本型（text）”，可以被省略。可以使用多字符 (*) 和单字符 (?) 通配符来指定多重文件。在非首次寻找文件时，参数值必须为空或被省略。
//    参数<2>的名称为“欲寻找文件的属性”，类型为“整数型（int）”，可以被省略。参数值可以为以下常量值或其和： 1、#只读文件； 2、#隐藏文件； 4、#系统文件； 16、#子目录； 32、#存档文件 。通过将这些常量值加起来可以一次设置多个文件属性。如果省略本参数，默认为搜寻除子目录外的所有文件。
//*/
//
//HANDLE 文件寻找句柄 = NULL;
//
//
//
//
//wstring 寻找文件(wstring 欲寻找的文件或目录名称,int 欲寻找的文件属性) {
//	HANDLE hFileFind = NULL;
//	WIN32_FIND_DATAW FileData;
//	wstring RetStr;
//	if (欲寻找的文件属性 <= 0) {
//		欲寻找的文件属性 = 1 | 2 | 4 | 32;
//	}
//	if (欲寻找的文件或目录名称.empty())
//	{
//		if (!文件寻找句柄)
//		{
//			return wstring();
//		}
//		else
//		{
//			if (!IsBadCodePtr((FARPROC)文件寻找句柄)) {
//				hFileFind = 文件寻找句柄;
//			}
//			else
//			{
//				return wstring();
//			}
//			while (FindNextFileW(hFileFind, &FileData)) {
//
//
//				if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//					RetStr = FileData.cFileName;
//					break;
//				}
//
//			}
//			return RetStr;
//		}
//		
//	}
//	else {
//		if (文件寻找句柄) {// 如果已经搜索过一次先进行释放。
//			FindClose(文件寻找句柄);
//			LocalFree(文件寻找句柄);
//			文件寻找句柄 = NULL;
//		}
//		hFileFind = FindFirstFileW(欲寻找的文件或目录名称.c_str(), &FileData);//重新申请
//		if (!hFileFind)//申请失败，返回空
//		{
//			return wstring();
//		}
//		文件寻找句柄 = hFileFind;//成功以后先保存到堆中
//		if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {  // 第一次寻找就寻找到了匹配的文件{
//			RetStr = FileData.cFileName;
//			return RetStr;
//		}
//		while (FindNextFileW(hFileFind, &FileData)) {
//			if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//				RetStr = FileData.cFileName;
//				break;
//			}
//		}
//		return RetStr;
//
//	}
//}
//string 寻找文件(string 欲寻找的文件或目录名称, int 欲寻找的文件属性) {
//	HANDLE hFileFind = NULL;
//	WIN32_FIND_DATAA FileData;
//	string RetStr;
//	if (欲寻找的文件属性 <= 0) {
//		欲寻找的文件属性 = 1 | 2 | 4 | 32;
//	}
//	if (欲寻找的文件或目录名称.empty())
//	{
//		if (!文件寻找句柄)
//		{
//			return string();
//		}
//		else
//		{
//			if (!IsBadCodePtr((FARPROC)文件寻找句柄)) {
//				hFileFind = 文件寻找句柄;
//			}
//			else
//			{
//				return string();
//			}
//			while (FindNextFileA(hFileFind, &FileData)) {
//
//
//				if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//					RetStr = FileData.cFileName;
//					break;
//				}
//
//			}
//			return RetStr;
//		}
//
//	}
//	else {
//		if (文件寻找句柄) {// 如果已经搜索过一次先进行释放。
//			FindClose(文件寻找句柄);
//			LocalFree(文件寻找句柄);
//			文件寻找句柄 = NULL;
//		}
//		hFileFind = FindFirstFileA(欲寻找的文件或目录名称.c_str(), &FileData);//重新申请
//		if (!hFileFind)//申请失败，返回空
//		{
//			return string();
//		}
//		文件寻找句柄 = hFileFind;//成功以后先保存到堆中
//		if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {  // 第一次寻找就寻找到了匹配的文件{
//			RetStr = FileData.cFileName;
//			return RetStr;
//		}
//		while (FindNextFileA(hFileFind, &FileData)) {
//			if ((欲寻找的文件属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//				RetStr = FileData.cFileName;
//				break;
//			}
//		}
//		return RetStr;
//
//	}
//}
//
//
//
//bool  寻找文件_释放句柄()
//{
//	HANDLE hFindFile;
//	if (IsBadCodePtr((FARPROC)文件寻找句柄)) {
//		return false;
//	}
//	hFindFile = 文件寻找句柄;  // 按寻找文件时的结构取值;
//	if (hFindFile) {
//		if (FindClose(hFindFile)) {
//			LocalFree(文件寻找句柄);
//			文件寻找句柄 = NULL;
//			return true;
//		}
//	}
//	return false;
//}
//
//string 下层寻找文件(string 文件名, int 欲寻找的文件属性, HANDLE* 传入句柄)
//{
//
//	_WIN32_FIND_DATAA FindFileData;
//	HANDLE 本次寻找句柄 = *(HANDLE*)传入句柄;
//	bool 是否找到;
//	是否找到 = 0;
//	if (文件名 != "" && !文件名.empty())
//	{
//		if (本次寻找句柄 && 本次寻找句柄 != (HANDLE)-1) {
//			FindClose(本次寻找句柄);
//		}
//		本次寻找句柄 = FindFirstFileA(文件名.c_str(), &FindFileData);
//		*传入句柄 = 本次寻找句柄;
//		if (本次寻找句柄 == (HANDLE)-1)
//			return {};
//		if (FindFileData.dwFileAttributes & 欲寻找的文件属性)
//		{
//			是否找到 = 1;
//
//		}
//	}
//	if (!本次寻找句柄 || 本次寻找句柄 == (HANDLE)-1) {
//		return {};
//	}
//	if (!是否找到)
//	{
//
//		if (!FindNextFileA(本次寻找句柄, &FindFileData))
//		{
//			return {};
//		}
//		while (!(欲寻找的文件属性 & FindFileData.dwFileAttributes))
//		{
//			if (!FindNextFileA(本次寻找句柄, &FindFileData)) {
//				return {};
//			}
//		}
//	}
//
//	return FindFileData.cFileName;
//}
//bool  下层寻找文件_释放句柄(HANDLE 文件寻找句柄)
//{
//	HANDLE hFindFile;
//	if (!文件寻找句柄)
//	{
//		return true;
//	}
//	if (IsBadCodePtr((FARPROC)文件寻找句柄)) {
//		return false;
//	}
//	hFindFile = 文件寻找句柄;  // 按寻找文件时的结构取值;
//	if (hFindFile) {
//		if (FindClose(hFindFile)) {
//			LocalFree(文件寻找句柄);
//			文件寻找句柄 = NULL;
//			return true;
//		}
//	}
//	return false;
//}



#pragma endregion













#pragma region 标准库测试
//#include <filesystem>
//#include<iostream>
//
////返回一个文本，用以表示所找到的文件名或目录名，它必须与所要求的名称格式或文件属性相匹配
////参数1:可以使用多字符 (*) 和单字符 (?) 通配符来指定多重文件。在非首次寻找文件时，参数值必须为空或被省略。
////参数2:参数值可以为以下常量值或其和： 1、只读文件； 2、隐藏文件； 4、系统文件； 16、子目录； 32、存档
//wstring  寻找文件W(const wstring& 欲寻找的文件或目录名称, int 欲寻找文件的属性)
//{
//	static HANDLE hFileFind;//根据这个句柄获取文件;
//	WIN32_FIND_DATAW FileData;
//	if (欲寻找文件的属性 <= 0) {
//		欲寻找文件的属性 = 1 | 2 | 4 | 32;
//	}
//	if (欲寻找的文件或目录名称.empty()) {
//		while (FindNextFileW(hFileFind, &FileData)) {
//			if (位与(欲寻找文件的属性, FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//				return FileData.cFileName;
//			}
//		}
//		FindClose(hFileFind);
//		hFileFind = 0;
//		return {  };
//	}
//	if (hFileFind != 0) {
//		FindClose(hFileFind);
//		hFileFind = 0;
//	}
//	hFileFind = FindFirstFileW(欲寻找的文件或目录名称.c_str(), &FileData);
//	if (hFileFind == (HANDLE)-1) {
//		hFileFind = 0;
//		return {  };
//	}
//	if ((欲寻找文件的属性 & FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//		return FileData.cFileName;
//	}
//
//	while (FindNextFileW(hFileFind, &FileData)) {
//		if (位与(欲寻找文件的属性, FileData.dwFileAttributes) == FileData.dwFileAttributes) {
//			return FileData.cFileName;
//		}
//	}
//	FindClose(hFileFind);
//	hFileFind = 0;
//	return {  };
//}
//
//
//#include <filesystem>
//#include <iostream>
//#include <string>
//
//namespace fs = std::filesystem; // 引用 std::filesystem 命名空间
//
//
//
//// 定义查找文件的函数
//vector<std::wstring> find_file(const std::wstring& path, fs::perms attributes = fs::perms::owner_read)
//{
//
//	// 如果指定了文件名，则执行查找操作，否则返回空字符串
//	vector<std::wstring> ret;
//	if (!path.empty())
//	{
//		try
//		{
//			// 创建文件查找迭代器
//			fs::directory_iterator it{ path };
//
//			// 遍历文件查找结果
//			for (const auto& entry : it)
//			{
//				// 获取文件属性
//				const auto file_attributes = entry.status().permissions();
//
//				// 如果文件属性与查找条件匹配，则返回文件名称
//				if ((attributes & file_attributes) == file_attributes)
//				{
//					ret.push_back(entry.path().wstring());
//				}
//			}
//		}
//		catch (const fs::filesystem_error& e)
//		{
//			// 如果文件查找失败，可以在这里处理错误信息
//		}
//
//	}
//	return ret;
//}
#pragma endregion





