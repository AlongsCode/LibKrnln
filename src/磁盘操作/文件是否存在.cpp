#include <filesystem>
#include <string>

KrnlnApi bool 文件是否存在(const std::string& file_name)
{
	return std::filesystem::exists(file_name);
}

KrnlnApi bool 文件是否存在(const std::wstring& file_name)
{
	return std::filesystem::exists(file_name);
}
