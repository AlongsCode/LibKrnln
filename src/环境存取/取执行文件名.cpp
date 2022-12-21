#include <filesystem>
#ifdef _WIN32
#include<windows.h>
#else//仅考虑linux
#include <unistd.h>
#endif 


KrnlnApi std::string 取执行文件名A()
{
	std::error_code ec;
	//尝试使用标准库获取
	std::filesystem::path exec_path = std::filesystem::read_symlink("/proc/self/exe", ec);
	if (ec)
	{
		if (ec.value() == ENOENT)//不存在??
		{
			return {};
		}
		else
		{
#ifdef _WIN32
			std::string Path = "";
			char szModule[MAX_PATH + 1] = { 0 };
			szModule[0] = '\0';
			if (::GetModuleFileNameA(NULL, szModule, MAX_PATH)) {

				Path = szModule;
				Path = Path.substr(1 + Path.find_last_of("\\"));

			}
			return Path;
#else//仅考虑Linux
			pid_t pid = getpid();
			std::vector<char> path(1024);
			int result = readlink(("/proc/" + std::to_string(pid) + "/exe").c_str(), path.data(), path.size());
			if (result == -1) {
				return "";
			}
			std::string exec_path(path.begin(), path.begin() + result);
			return exec_path.substr(exec_path.find_last_of("/") + 1);

#endif // _WIN32
		}
	}
	return exec_path.filename().string();
}

KrnlnApi std::wstring 取执行文件名W()
{
	std::error_code ec;
	//尝试使用标准库获取
	std::filesystem::path exec_path = std::filesystem::read_symlink(L"/proc/self/exe", ec);
	if (ec)
	{
		if (ec.value() == ENOENT)//不存在?
		{
			return {};
		}
		else
		{
#ifdef _WIN32
			std::wstring Path = L"";
			wchar_t szModule[MAX_PATH + 1] = { 0 };
			szModule[0] = L'\0';
			if (::GetModuleFileNameW(NULL, szModule, MAX_PATH)) {

				Path = szModule;
				Path = Path.substr(1 + Path.find_last_of(L"\\"));

			}
			return Path;
#else //仅考虑Linux
			pid_t pid = getpid();
			std::vector<wchar_t> path(1024);
			int result = readlink(L("/proc/" + std::to_wstring(pid) + L"/exe").c_str(), path.data(), path.size());
			if (result == -1) {
				return L"";
			}
			std::wstring exec_path(path.begin(), path.begin() + result);
			return exec_path.substr(exec_path.find_last_of(L"/") + 1);
#endif 
		}
	}
	return exec_path.filename().wstring();
}
