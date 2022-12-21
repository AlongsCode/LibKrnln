#include"string"
using namespace std;




KrnlnApi string 字符A(char 欲取其字符的字符代码) {

	if (欲取其字符的字符代码 == 0)
		return "";
	char a[2] = { 欲取其字符的字符代码 ,'\0' };
	string Ret;
	Ret.append(a);
	return Ret;
}

KrnlnApi wstring 字符W(wchar_t 欲取其字符的字符代码) {

	if (欲取其字符的字符代码 == 0)
		return L"";
	wchar_t a[2] = { 欲取其字符的字符代码 ,L'\0' };
	wstring Ret;
	Ret.append(a);
	return Ret;
}