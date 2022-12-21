#include"string"
using namespace std;

/*
取文本型数据的长度，不包含结束0
<std::string> 类型变量 <文本数据> 参数值指定欲检查其长度的文本数据
*/

KrnlnApi size_t 取文本长度(const string& 文本数据) {
	return 文本数据.size();
}
KrnlnApi size_t 取文本长度(const  wstring& 文本数据) {
	return 文本数据.size();
}