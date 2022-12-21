#include"string"
using namespace std;




/*
返回一个文本，其中包含指定文本中从右边算起指定数量的字符
<int> 类型变量 <欲取出字符的数目>

*/
KrnlnApi string 取文本右边(const std::string& 欲取其部分的文本, size_t 欲取出字符的数目) {

	if (欲取其部分的文本.empty()) {
		return "";
	}
	if (欲取出字符的数目 >= 欲取其部分的文本.size()) {
		return 欲取其部分的文本;
	}
	return (欲取其部分的文本.substr(欲取其部分的文本.length() - 欲取出字符的数目));

}

KrnlnApi wstring 取文本右边(const  wstring& 欲取其部分的文本, size_t 欲取出字符的数目) {

	if (欲取其部分的文本.empty()) {
		return L"";
	}
	if (欲取出字符的数目 >= 欲取其部分的文本.size()) {
		return 欲取其部分的文本;
	}
	return (欲取其部分的文本.substr(欲取其部分的文本.length() - 欲取出字符的数目));
}
