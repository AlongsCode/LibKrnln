#include"string"
using namespace std;




KrnlnApi string 删首尾空(string 欲删除空格的文本)
{
	if (欲删除空格的文本.empty())
	{
		return 欲删除空格的文本;
	}

	欲删除空格的文本.erase(0, 欲删除空格的文本.find_first_not_of(" "));
	欲删除空格的文本.erase(欲删除空格的文本.find_last_not_of(" ") + 1);
	return 欲删除空格的文本;
}

KrnlnApi wstring 删首尾空(wstring 欲删除空格的文本)
{
	if (欲删除空格的文本.empty())
	{
		return 欲删除空格的文本;
	}

	欲删除空格的文本.erase(0, 欲删除空格的文本.find_first_not_of(L" "));
	欲删除空格的文本.erase(欲删除空格的文本.find_last_not_of(L" ") + 1);
	return 欲删除空格的文本;
}