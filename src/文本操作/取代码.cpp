#include"string"




/*
返回文本中指定位置处字符的代码。如果指定位置超出文本长度，返回0
<int> 类型变量 <欲取其代码的字符位置> 1为首位置，2为第2个位置，如此类推。如果本参数被省略，默认为首位置

*/
KrnlnApi int 取代码(const std::string& 欲取字符代码的文本, size_t 欲取其代码的字符位置) {
	if (欲取字符代码的文本.empty()) {
		return 0;
	}
	if (欲取其代码的字符位置 < 1)
	{
		欲取其代码的字符位置 = 1;
	}
	if (欲取其代码的字符位置 > 欲取字符代码的文本.size()) {
		return 0;
	}
	const char* 文本 = 欲取字符代码的文本.c_str();
	intptr_t nIdx = (欲取其代码的字符位置 - 1);
	if (nIdx < 0) {
		return 0;
	}
	const char* cp = 文本;
	if (!cp) {
		return 0;
	}
	const char* pStart = 文本 + nIdx;
	//检查给定的索引是否越界，并且不用遍历整块内存。
	while (*cp && cp < pStart) {
		cp++;
	}
	return (int)*cp;
}


KrnlnApi int 取代码(const std::wstring& 欲取字符代码的文本, size_t 欲取其代码的字符位置) {
	if (欲取字符代码的文本.empty()) {
		return 0;
	}
	if (欲取其代码的字符位置 < 1)
	{
		欲取其代码的字符位置 = 1;
	}
	if (欲取其代码的字符位置 > 欲取字符代码的文本.size()) {
		return 0;
	}
	const wchar_t* 文本 = 欲取字符代码的文本.c_str();
	intptr_t nIdx = (欲取其代码的字符位置 - 1);

	if (nIdx < 0) return 0;

	const wchar_t* cp = 文本;
	if (!cp) return 0;

	const wchar_t* pStart = 文本 + nIdx;

	//检查给定的索引是否越界，并且不用遍历整块内存。
	while (*cp && cp < pStart)
		cp++;

	return (int)*cp;
}
