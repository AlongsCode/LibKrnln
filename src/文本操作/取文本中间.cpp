#include"string"
using namespace std;




/*
返回一个文本，其中包含指定文本中从指定位置算起指定数量的字符
<int> 类型变量 <欲取出字符的数目>

*/
KrnlnApi string 取文本中间(const std::string& 欲取其部分的文本, size_t 起始取出位置, size_t 欲取出字符的数目) {
	return (欲取其部分的文本.substr(起始取出位置 - 1, 欲取出字符的数目));
}

KrnlnApi wstring 取文本中间(const  wstring& 欲取其部分的文本, size_t 起始取出位置, size_t 欲取出字符的数目) {
	return (欲取其部分的文本.substr(起始取出位置 - 1, 欲取出字符的数目));
}