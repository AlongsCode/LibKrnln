#include <fstream>  
#include <vector>   
#ifndef _MSVC_LANG
#undef _MSVC_LANG
#define _MSVC_LANG __cplusplus
#endif

#define  CANUSEMAPFILE 999999//c++20不行，什么时候可以了直接替换
#if _MSVC_LANG > CANUSEMAPFILE
#include <memory_resource>  // 内存映射
KrnlnApi std::vector<unsigned char> 读入文件(const std::string& filename) {
	// 创建一个内存资源来映射文件
	std::pmr::monotonic_buffer_resource mem_res;
	std::pmr::map_file(filename, mem_res);
	// 从内存资源中获取指向文件数据的指针
	const void* data = mem_res.data();
	// 获取文件长度
	size_t length = mem_res.size();
	// 将文件数据拷贝到 vector<unsigned char>
	std::vector<unsigned char> result;
	result.reserve(length);
	std::copy_n(
		reinterpret_cast<const unsigned char*>(data),
		length,
		std::back_inserter(result)
	);
	// 文件内存映射会在内存资源析构时自动解除
	return result;
}
KrnlnApi std::vector<unsigned char> 读入文件(const std::wstring& filename) {
	// 创建一个内存资源来映射文件
	std::pmr::monotonic_buffer_resource mem_res;
	std::pmr::map_file(filename, mem_res);

	// 从内存资源中获取指向文件数据的指针
	const void* data = mem_res.data();
	// 获取文件长度
	size_t length = mem_res.size();

	// 将文件数据拷贝到 vector<unsigned char>
	std::vector<unsigned char> result;
	result.reserve(length);
	std::copy_n(reinterpret_cast<const unsigned char*>(data), length,
		std::back_inserter(result));

	// 文件内存映射会在内存资源析构时自动解除
	return result;
}
#else
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
		file.read((char*)&data[0], length);
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
		file.read((char*)&data[0], length);
	}
	// 关闭文件
	file.close();
	return data;
}
#endif