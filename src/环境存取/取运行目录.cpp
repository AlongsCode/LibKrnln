#include<filesystem>
KrnlnApi std::string 取运行目录A() {
	return std::filesystem::current_path().string();
}
KrnlnApi std::wstring 取运行目录W() {
	return std::filesystem::current_path().wstring();
}
