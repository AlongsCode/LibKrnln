#include <fstream>  
#include <vector>   


KrnlnApi std::vector<unsigned char> 读入文件(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	std::vector<unsigned char> data;

	// 如果文件打开成功
	if (file) {
		// 获取文件长度
		file.seekg(0, std::ios::end);
		std::streampos length = file.tellg();
		// 重置文件指针到文件开头
		file.seekg(0, std::ios::beg);
		// 读取整个文件的所有字节到 vector<unsigned char>
		data.resize((size_t)length);
		file.read(reinterpret_cast<char*>(&data[0]), length);
	}
	// 关闭文件
	file.close();
	return data;
}

KrnlnApi std::vector<unsigned char> 读入文件(const std::wstring& filename) {
	std::ifstream file(filename, std::ios::binary);
	std::vector<unsigned char> data;

	// 如果文件打开成功
	if (file) {
		// 获取文件长度
		file.seekg(0, std::ios::end);
		std::streampos length = file.tellg();
		// 重置文件指针到文件开头
		file.seekg(0, std::ios::beg);
		// 读取整个文件的所有字节到 vector<unsigned char>
		data.resize((size_t)length);
		file.read(reinterpret_cast<char*>(&data[0]), length);
	}
	// 关闭文件
	file.close();
	return data;
}
