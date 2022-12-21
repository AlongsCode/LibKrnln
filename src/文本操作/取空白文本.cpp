#include"string"
using namespace std;




/*
返回具有指定数目半角空格的文本
<int> 类型变量 <重复次数>

*/
KrnlnApi string 取空白文本A(size_t 重复次数) {
	size_t size = 重复次数;
	std::string blanks(size, ' ');
	return blanks;
}

KrnlnApi wstring 取空白文本W(size_t 重复次数) {
	size_t size = 重复次数;
	std::wstring blanks(size, L' ');
	return blanks;
}