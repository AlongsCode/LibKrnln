#include <filesystem>



KrnlnApi bool 创建目录(const std::string& 路径名称, bool 强制创建) {
	std::filesystem::path p(路径名称);
	if (!强制创建)
	{
		if (!std::filesystem::exists(p.parent_path())) {
			return false;
		}
	}
	return std::filesystem::create_directories(路径名称);
}
KrnlnApi bool 创建目录(const std::wstring& 路径名称, bool 强制创建) {
	std::filesystem::path p(路径名称);
	if (!强制创建)
	{
		if (!std::filesystem::exists(p.parent_path())) {
			return false;
		}
	}
	return std::filesystem::create_directories(路径名称);
}
