#include"string"
using namespace std;





/*
返回一个文本，其中包含指定次数的文本重复结果
<std::string> 类型变量 <待重复文本> 该文本将用于建立返回的文本。如果为空，将返回一个空文本

*/
KrnlnApi string 取重复文本(size_t 重复次数, const std::string& 待重复文本) {

	size_t nLen = 待重复文本.size();
	if (待重复文本.empty())
	{
		return "";
	}
	if (nLen == 0 || 重复次数 <= 0) {
		return "";
	}
	size_t nBuf = nLen * 重复次数;
	string str;
	for (size_t i = 0; i < 重复次数; i++)
	{
		str.append(待重复文本);
	}

	return str;
}


KrnlnApi wstring 取重复文本(size_t 重复次数, const  wstring& 待重复文本) {

	size_t nLen = 待重复文本.size();
	if (待重复文本.empty())
	{
		return L"";
	}
	if (nLen == 0 || 重复次数 <= 0) {
		return L"";
	}
	size_t nBuf = nLen * 重复次数;
	wstring str;
	for (size_t i = 0; i < 重复次数; i++)
	{
		str.append(待重复文本);
	}

	return str;
}