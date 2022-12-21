#include"string"

using namespace std;




string 到大写(const string& 欲变换的文本);

wstring 到大写(const  wstring& 欲变换的文本);

/*
返回一个整数值，指定一文本在另一文本中最先出现的位置，位置值从 1 开始。如果未找到，返回-1
<bool> 类型变量 <是否不区分大小写> 为真不区分大小写，为假区分

*/

KrnlnApi intptr_t 寻找文本(string 被搜寻的文本, string 欲寻找的文本, size_t 起始搜寻位置, bool 是否不区分大小写)

{

	if (是否不区分大小写)
	{
		被搜寻的文本 = 到大写(被搜寻的文本);
		欲寻找的文本 = 到大写(欲寻找的文本);
	}
	intptr_t Ret = 被搜寻的文本.find(欲寻找的文本.c_str(), 起始搜寻位置);
	if (Ret != 被搜寻的文本.npos)
	{
		return Ret + 1;
	}

	return -1;
}



KrnlnApi intptr_t 寻找文本(wstring 被搜寻的文本, wstring 欲寻找的文本, size_t 起始搜寻位置, bool 是否不区分大小写)

{
	if (是否不区分大小写)
	{
		被搜寻的文本 = 到大写(被搜寻的文本);
		欲寻找的文本 = 到大写(欲寻找的文本);
	}
	intptr_t Ret = 被搜寻的文本.find(欲寻找的文本.c_str(), 起始搜寻位置);
	if (Ret != 被搜寻的文本.npos)
	{
		return Ret + 1;
	}
	return -1;
}




