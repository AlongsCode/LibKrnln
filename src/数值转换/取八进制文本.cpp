#include<string>
using namespace std;

KrnlnApi string 取八进制文本A(int 欲取进制文本的数值) {

	char pText[256] = { 0 };
	sprintf_s(pText, 256, "%o", 欲取进制文本的数值);

	return pText;
}


KrnlnApi wstring 取八进制文本W(int 欲取进制文本的数值) {

	wchar_t pText[256] = { 0 };
	swprintf_s(pText, 256, L"%o", 欲取进制文本的数值);
	return  pText;
}