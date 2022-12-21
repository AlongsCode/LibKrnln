#include"string"
using namespace std;

/*
返回一个文本，其中包含被删除了尾部全角或半角空格的指定文本
<std::string> 类型变量 <欲删除空格的文本>

*/
KrnlnApi string 删尾空(string 欲删除空格的文本)
{
	if (欲删除空格的文本.empty())
	{
		return 欲删除空格的文本;
	}
	欲删除空格的文本.erase(欲删除空格的文本.find_last_not_of(" ") + 1);
	return 欲删除空格的文本;
}
KrnlnApi wstring 删尾空(wstring 欲删除空格的文本)
{
	if (欲删除空格的文本.empty())
	{
		return 欲删除空格的文本;
	}
	欲删除空格的文本.erase(欲删除空格的文本.find_last_not_of(L" ") + 1);
	return 欲删除空格的文本;
}
