#include <string>

KrnlnApi std::string 取父路径(const std::string& file_or_directory_name)
{
	std::string result = file_or_directory_name;
	if (!result.empty() && result.back() == '\\') {
		result.pop_back();
	}
	size_t pos = result.find_last_of("\\");
	return result.substr(0, pos);
}
KrnlnApi std::wstring 取父路径(const std::wstring& file_or_directory_name)
{
	std::wstring result = file_or_directory_name;
	if (!result.empty() && result.back() == '\\') {
		result.pop_back();
	}
	size_t pos = result.find_last_of(L"\\");
	return result.substr(0, pos);
}