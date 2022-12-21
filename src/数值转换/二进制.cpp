
#include<string>


KrnlnApi long 二进制(const std::string& 二进制文本常量) {
	return strtol(二进制文本常量.c_str(), NULL, 2);

}

KrnlnApi long 二进制(const std::wstring& 二进制文本常量) {
	return wcstol(二进制文本常量.c_str(), NULL, 2);

}