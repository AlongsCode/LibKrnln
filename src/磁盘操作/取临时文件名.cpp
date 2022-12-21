#include <filesystem>



KrnlnApi std::string 取临时文件名A(const std::string& dir_name) {
	// 获取临时文件夹的路径
	std::filesystem::path temp_dir = std::filesystem::temp_directory_path();
	if (!dir_name.empty()) {
		temp_dir = dir_name;
	}

	// 确保临时文件夹的路径以斜杠结尾
	if (!temp_dir.has_stem()) {
		temp_dir /= "";
	}
	//根据时间生成随机文件名
	std::filesystem::path temp_file_name;
	do {
		time_t num = time(0);
		std::stringstream ss;
		ss << std::hex << num;
		std::string hex_string = ss.str() + ".tmp";
		temp_file_name = temp_dir / hex_string;
	} while (std::filesystem::exists(temp_file_name));

	return temp_file_name.string();
}

KrnlnApi std::wstring 取临时文件名W(const std::wstring& dir_name) {
	// 获取临时文件夹的路径
	std::filesystem::path temp_dir = std::filesystem::temp_directory_path();
	if (!dir_name.empty()) {
		temp_dir = dir_name;
	}

	// 确保临时文件夹的路径以斜杠结尾
	if (!temp_dir.has_stem()) {
		temp_dir /= "";
	}
	//根据时间生成随机文件名
	std::filesystem::path temp_file_name;
	do {
		time_t num = time(0);
		std::wstringstream ss;
		ss << std::hex << num;
		std::wstring hex_string = ss.str() + L".tmp";
		temp_file_name = temp_dir / hex_string;
	} while (std::filesystem::exists(temp_file_name));

	return temp_file_name.wstring();
}
