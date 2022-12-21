#include"string"
#include <algorithm>
using namespace std;


string 到大写(const string& 欲变换的文本);

wstring 到大写(const wstring& 欲变换的文本);
/*
拷贝，因为中间会有一次到大写，还是需要拷贝一次，无所谓了。
*/
KrnlnApi intptr_t 倒找文本(wstring 被搜寻的文本, wstring 欲寻找的文本, intptr_t 起始搜寻位置, bool 是否不区分大小写) {
	size_t  Ret = 0;

	if (是否不区分大小写)
	{
		被搜寻的文本 = 到大写(被搜寻的文本);
		欲寻找的文本 = 到大写(欲寻找的文本);
	}
	if (起始搜寻位置 == -1)
	{
		Ret = 被搜寻的文本.rfind(欲寻找的文本.c_str());
	}
	else
	{
		Ret = 被搜寻的文本.rfind(欲寻找的文本.c_str(), 起始搜寻位置 - 2);
	}

	if (Ret == 被搜寻的文本.npos)
	{
		return -1;
	}

	return Ret + 1;


}
KrnlnApi intptr_t 倒找文本(string 被搜寻的文本, string 欲寻找的文本, intptr_t 起始搜寻位置, bool 是否不区分大小写) {
	size_t  Ret = 0;
	if (是否不区分大小写)
	{
		被搜寻的文本 = 到大写(被搜寻的文本);
		欲寻找的文本 = 到大写(欲寻找的文本);
	}
	if (起始搜寻位置 == -1)
	{
		Ret = 被搜寻的文本.rfind(欲寻找的文本.c_str());
	}
	else
	{
		Ret = 被搜寻的文本.rfind(欲寻找的文本.c_str(), 起始搜寻位置 - 2);
	}

	if (Ret == 被搜寻的文本.npos)
	{
		return -1;
	}
	return Ret + 1;

}