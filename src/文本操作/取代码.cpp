#include"string"




/*
返回文本中指定位置处字符的代码。如果指定位置超出文本长度，返回0
<int> 类型变量 <欲取其代码的字符位置> 1为首位置，2为第2个位置，如此类推。如果本参数被省略，默认为首位置

*/
KrnlnApi int 取代码(const std::string& text, size_t idx) {
	if (text.empty()) {
		return 0;
	}
	if (idx < 1) {
		idx = 1;
	}
	if (idx > text.size()) {
		return 0;
	}
	return (int)text.at(idx - 1);
}


KrnlnApi short 取代码(const std::wstring& text, size_t idx) {
	if (text.empty()) {
		return 0;
	}
	if (idx < 1) {
		idx = 1;
	}
	if (idx > text.size()) {
		return 0;
	}
	return text.at(idx - 1);
}
