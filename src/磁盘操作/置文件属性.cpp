#include"string"
#include"windows.h"
using namespace std;

#ifdef _WIN32
KrnlnApi bool 置文件属性(const string& 欲设置其属性的文件名称, int 欲设置为的属性值) {


	return SetFileAttributesA(欲设置其属性的文件名称.c_str(), 欲设置为的属性值);


}


KrnlnApi bool 置文件属性(const wstring& 欲设置其属性的文件名称, int 欲设置为的属性值) {


	return SetFileAttributesW(欲设置其属性的文件名称.c_str(), 欲设置为的属性值);


}
#endif // _WIN32

