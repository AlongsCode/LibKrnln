#include<vector>

KrnlnApi std::vector<unsigned char> 字节集拼接(std::vector<unsigned char> 字节集1, const std::vector<unsigned char>& 字节集2) {
	字节集1.insert(字节集1.end(), 字节集2.begin(), 字节集2.end());
	return 字节集1;
}