#include"string"
using namespace std;



/*
返回指定内存指针所指向地址处的文本，注意调用本命令前一定要确保所提供的内存指针真实有效，且指向一个以零字符结束的文本串。本命令的最佳使用场合就是在易语言回调子程序和易语言DLL公开子程序用作获取外部数据
<int> 类型变量 <内存文本指针> 本参数提供指向一个以零字符结束的文本串内存指针值

*/
KrnlnApi string 指针到文本A(void* 内存文本指针) {
	if (!内存文本指针 || strlen((char*)(内存文本指针)) == 0)
	{
		return "";
	}
	return (char*)(内存文本指针);
}

KrnlnApi wstring 指针到文本W(void* 内存文本指针) {
	if (!内存文本指针 || wcslen((wchar_t*)(内存文本指针)) == 0)
	{
		return L"";
	}
	return (wchar_t*)(内存文本指针);
}

