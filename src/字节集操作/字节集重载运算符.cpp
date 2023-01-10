#include<vector>
KrnlnApi std::vector<unsigned char> operator+(const std::vector<unsigned char>& 字节集1, const std::vector<unsigned char>& 字节集2) {
	std::vector<unsigned char> result;
	result.reserve(字节集1.size() + 字节集2.size());
	result.insert(result.end(), 字节集1.begin(), 字节集1.end());
	result.insert(result.end(), 字节集2.begin(), 字节集2.end());
	return result;
}