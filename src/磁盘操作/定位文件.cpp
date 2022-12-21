#ifdef _WIN32//仅win下可用
#include<Shlobj.h>
#include <filesystem>
KrnlnApi bool 定位文件(const std::wstring& 文件路径, bool 编辑模式)
{
	if (!std::filesystem::exists(文件路径)) {//文件不存在
		return false;
	}
	LPITEMIDLIST lng_pidl = nullptr;
	bool initialized = CoInitialize(0) == S_OK;//初始化过或者没有初始化成功
	lng_pidl = ILCreateFromPathW(文件路径.c_str());
	if (!lng_pidl) {
		if (initialized) {//在本函数中初始化的com控件
			CoUninitialize();
		}
		return false;
	}
	bool success = SHOpenFolderAndSelectItems(lng_pidl, 0, 0, 编辑模式 ? 1 : 0) == S_OK;
	SHFree(lng_pidl);
	if (initialized) {
		CoUninitialize();
	}
	return success;
}
KrnlnApi bool 定位文件(const std::string& 文件路径, bool 编辑模式)
{
	if (!std::filesystem::exists(文件路径)) {//文件不存在
		return false;
	}
	LPITEMIDLIST lng_pidl = nullptr;
	bool initialized = CoInitialize(0) == S_OK;//初始化过或者没有初始化成功
	lng_pidl = ILCreateFromPathA(文件路径.c_str());
	if (!lng_pidl) {
		if (initialized) {//在本函数中初始化的com控件
			CoUninitialize();
		}
		return false;
	}
	bool success = SHOpenFolderAndSelectItems(lng_pidl, 0, 0, 编辑模式 ? 1 : 0) == S_OK;
	SHFree(lng_pidl);
	if (initialized) {
		CoUninitialize();
	}
	return success;
}
#endif // _WIN32

