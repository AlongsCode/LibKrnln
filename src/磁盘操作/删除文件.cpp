#include<string>


#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi bool 删除文件(const string& 欲删除的文件名) {
	return DeleteFileA(欲删除的文件名.c_str());
}

KrnlnApi bool 删除文件(const wstring 欲删除的文件名) {
	return DeleteFileW(欲删除的文件名.c_str());
}

#else
#include"direct.h"

KrnlnApi bool 删除文件(const string& 欲删除的目录名称) {

	return remove(欲删除的目录名称.c_str()) == 0;
}
KrnlnApi bool 删除文件(const wstring& 欲删除的目录名称) {
	return _wremove(欲删除的目录名称.c_str()) == 0;
}
#endif
