#include"string"
using namespace std;
//逻辑比较 - 近似等于
/*
	调用格式： 〈逻辑型〉 近似等于 （文本型 被比较文本，文本型 比较文本） - 系统核心支持库->逻辑比较
	英文名称：like
	当比较文本在被比较文本的首部被包容时返回真，否则返回假，运算符号为“?=”或“≈”。本命令为初级命令。
	参数<1>的名称为“被比较文本”，类型为“文本型（text）”。
	参数<2>的名称为“比较文本”，类型为“文本型（text）”。
*/
KrnlnApi bool 近似等于(string 被比较文本, string 比较文本)
{
	char* str1;
	char* str2;
	if (被比较文本.empty()) {
		str1 = 0;
	}
	else {
		str1 = const_cast<char*>(被比较文本.c_str());
	}
	if (比较文本.empty()) {
		str2 = 0;
	}
	else {
		str2 = const_cast<char*>(比较文本.c_str());
	}

	if (!str1 || !str2 || !*str1 || !*str2) return false; //空文本直接返回

	while (*str1 && *str2 && *str1 == *str2)
		str1++, str2++;
	return *str2 == 0;
}


KrnlnApi bool 近似等于(wstring 被比较文本, wstring 比较文本)
{
	wchar_t* str1;
	wchar_t* str2;
	if (被比较文本.empty()) {
		str1 = 0;
	}
	else {
		str1 = const_cast<wchar_t*>(被比较文本.c_str());
	}
	if (比较文本.empty()) {
		str2 = 0;
	}
	else {
		str2 = const_cast<wchar_t*>(比较文本.c_str());
	}

	if (!str1 || !str2 || !*str1 || !*str2) return false; //空文本直接返回

	while (*str1 && *str2 && *str1 == *str2)
		str1++, str2++;
	return *str2 == 0;
}
KrnlnApi bool 约等于(wstring 参1, wstring 参2)
{

	size_t 计次;
	wchar_t 是否不为结束符;
	bool result;
	const wchar_t* 参数1 = 参1.c_str();
	const wchar_t* 参数2 = 参2.c_str();

	if (参数1 && 参数2 && *参数1 && *参数2)
	{
		计次 = 参数1 - 参数2;
		do
		{
			if (!*参数2)
				break;
			if (参数2[计次] != *参数2)
				break;
			是否不为结束符 = (参数2++)[计次 + 1];
		} while (是否不为结束符);
		result = *参数2 == 0;
	}
	else
	{
		result = 0;
	}

	return result;
}
KrnlnApi bool 约等于(string 参1, string 参2)
{

	size_t 计次;
	char 是否不为结束符;
	bool result;
	const char* 参数1 = 参1.c_str();
	const char* 参数2 = 参2.c_str();

	if (参数1 && 参数2 && *参数1 && *参数2)
	{
		计次 = 参数1 - 参数2;
		do
		{
			if (!*参数2)
				break;
			if (参数2[计次] != *参数2)
				break;
			是否不为结束符 = (参数2++)[计次 + 1];
		} while (是否不为结束符);
		result = *参数2 == 0;
	}
	else
	{
		result = 0;
	}

	return result;
}