#include <filesystem>
#include <string>

KrnlnApi bool 清空目录(const std::string& 要删除文件的目录, const std::string& 文件类型, bool 删除文件夹)
{

	std::string dir = 要删除文件的目录;
	if (!dir.empty() && dir.back() != '/' && dir.back() != '\\')
		dir += '/';

	bool success = true;
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{

		if (entry.is_directory() && 删除文件夹)//判断是否为目录
		{

			if (!std::filesystem::remove(entry))
			{
				success = false;
				break;
			}

		}
		else {//不为目录再判断
			if (文件类型 != "" && entry.path().extension().string() != "." + 文件类型)//输入了指定类型不匹配，跳出循环
				continue;
			else if (!entry.is_directory())
			{
				if (!std::filesystem::remove(entry))
				{
					success = false;
					break;
				}
			}
		}


	}

	return success;

}


KrnlnApi bool 清空目录(const std::wstring& 要删除文件的目录, const std::wstring& 文件类型, bool 删除文件夹)
{

	std::wstring dir = 要删除文件的目录;
	if (!dir.empty() && dir.back() != L'/' && dir.back() != L'\\')
		dir += L'/';

	bool success = true;
	for (const auto& entry : std::filesystem::directory_iterator(dir))
	{

		if (entry.is_directory() && 删除文件夹)//判断是否为目录
		{

			if (!std::filesystem::remove(entry))
			{
				success = false;
				break;
			}

		}
		else {//不为目录再判断
			if (文件类型 != L"" && entry.path().extension().wstring() != L"." + 文件类型)//输入了指定类型不匹配，跳出循环
				continue;
			else if (!entry.is_directory())
			{
				if (!std::filesystem::remove(entry))
				{
					success = false;
					break;
				}
			}
		}


	}

	return success;

}