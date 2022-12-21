#include"string"

using namespace std;


KrnlnApi long 十六进制(const wstring& 十六进制文本常量) {

	return wcstol(十六进制文本常量.c_str(), NULL, 16);



}


KrnlnApi long 十六进制(const string& 十六进制文本常量) {

	return strtol(十六进制文本常量.c_str(), NULL, 16);
}