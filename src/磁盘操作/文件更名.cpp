#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include<filesystem>
KrnlnApi bool 文件更名(const std::wstring& 欲更名的原文件或目录名, const std::wstring& 欲更改为的现文件或目录名) {
	bool success = false;
	try
	{
		std::filesystem::rename(欲更名的原文件或目录名, 欲更改为的现文件或目录名);
		success = true;
	}
	catch (const std::filesystem::filesystem_error)
	{
		// 文件更名操作失败，抛出异常
	}
	return success;
}

KrnlnApi bool 文件更名(const std::string& 欲更名的原文件或目录名, const std::string& 欲更改为的现文件或目录名) {

	bool success = false;
	try
	{
		std::filesystem::rename(欲更名的原文件或目录名, 欲更改为的现文件或目录名);
		success = true;
	}
	catch (const std::filesystem::filesystem_error)
	{
		// 文件更名操作失败，抛出异常
	}
	return success;

}


