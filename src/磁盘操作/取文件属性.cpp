
#include"string"
#include"windows.h"
using namespace std;

KrnlnApi int 取文件属性(const string& 文件名) {
	const DWORD dwFlags = ::GetFileAttributesA(文件名.c_str());
	return (dwFlags == 0xffffffff ? -1 : (INT)dwFlags);


}
KrnlnApi int 取文件属性(const wstring& 文件名) {

	const DWORD dwFlags = ::GetFileAttributesW(文件名.c_str());
	return (dwFlags == 0xffffffff ? -1 : (INT)dwFlags);

}





