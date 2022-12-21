#include <filesystem>
KrnlnApi bool 移动文件(const std::wstring& 被移动的文件, const std::wstring& 移动到的位置)
{
	// 尝试使用 std::filesystem::rename 移动文件,函数没有返回值，仅在失败时抛出异常，实际上更为安全
	try
	{
		std::filesystem::rename(被移动的文件, 移动到的位置);
		return true;
	}
	// 如果 rename 失败，则使用 std::filesystem::copy 和 std::filesystem::remove 实现文件移动
	catch (const std::filesystem::filesystem_error&)
	{
		std::filesystem::copy(被移动的文件, 移动到的位置);
		std::filesystem::remove(被移动的文件);
		return true;
	}
	// 如果发生未知异常，则返回 false
	catch (...)
	{
		return false;
	}
}



KrnlnApi bool 移动文件(const std::string& 被移动的文件, const std::string& 移动到的位置)
{
	// 尝试使用 std::filesystem::rename 移动文件,函数没有返回值，仅在失败时抛出异常，实际上更为安全
	try
	{
		std::filesystem::rename(被移动的文件, 移动到的位置);
		return true;
	}
	// 如果 rename 失败，则使用 std::filesystem::copy 和 std::filesystem::remove 实现文件移动
	catch (const std::filesystem::filesystem_error&)
	{
		std::filesystem::copy(被移动的文件, 移动到的位置);
		std::filesystem::remove(被移动的文件);
		return true;
	}
	// 如果发生未知异常，则返回 false
	catch (...)
	{
		return false;
	}
}
