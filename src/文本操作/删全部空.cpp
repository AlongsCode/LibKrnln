#include"string"
using namespace std;

KrnlnApi wstring 删全部空(wstring 欲删除空格的文本)
{
	wstring mark = L" ";
	size_t nSize = mark.size();
	if (欲删除空格的文本.empty() || 欲删除空格的文本 == L"") {
		return L"";
	}
	while (1)
	{
		size_t pos = 欲删除空格的文本.find(mark);    //  尤其是这里
		if (pos == wstring::npos)
		{
			return 欲删除空格的文本;
		}

		欲删除空格的文本.erase(pos, nSize);
	}
}
KrnlnApi string 删全部空(string 欲删除空格的文本)
{
	string mark = " ";
	size_t nSize = mark.size();
	if (欲删除空格的文本.empty() || 欲删除空格的文本 == "") {
		return "";
	}
	while (1)
	{
		size_t pos = 欲删除空格的文本.find(mark);    //  尤其是这里
		if (pos == string::npos)
		{
			return 欲删除空格的文本;
		}

		欲删除空格的文本.erase(pos, nSize);
	}
}