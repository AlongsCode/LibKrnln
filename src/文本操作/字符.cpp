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

KrnlnApi wstring 字符W(wchar_t code) {
	if (code == 0)
		return L"";
	return std::wstring(1, code);
}