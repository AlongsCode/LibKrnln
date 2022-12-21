#include"string"
#include <vector>
using namespace std;




/*
将指定文本进行分割，返回分割后的一维文本数组
<int> 类型变量 <要返回的子文本数目> 如果被省略，则默认返回所有的子文本

*/
KrnlnApi std::vector<string> 分割文本(const string& 待分割文本, const string& 用作分割的文本, size_t 要返回的子文本数目) {
	std::vector<string> 返回文本;
	if (用作分割的文本.empty() || 待分割文本 == "")
	{
		返回文本.push_back(待分割文本);
		return 返回文本;
	}
	size_t start = 0, index = 待分割文本.find_first_of(用作分割的文本, 0);
	while (index != 待分割文本.npos)
	{
		if (start != index)
			返回文本.push_back(待分割文本.substr(start, index - start));
		start = index + 1;
		index = 待分割文本.find_first_of(用作分割的文本, start);
	}
	if (待分割文本.substr(start) != "")
	{
		返回文本.push_back(待分割文本.substr(start));
	}
	if (要返回的子文本数目 != -1 && 要返回的子文本数目 <= 返回文本.size())
	{
		返回文本.resize(要返回的子文本数目);
	}
	return 返回文本;
}

KrnlnApi std::vector<wstring> 分割文本(const  wstring& 待分割文本, const  wstring& 用作分割的文本, size_t 要返回的子文本数目) {
	std::vector<wstring> 返回文本;
	if (用作分割的文本.empty() || 待分割文本 == L"")
	{
		返回文本.push_back(待分割文本);
		return 返回文本;
	}
	size_t start = 0, index = 待分割文本.find_first_of(用作分割的文本, 0);
	while (index != 待分割文本.npos)
	{
		if (start != index)
			返回文本.push_back(待分割文本.substr(start, index - start));
		start = index + 1;
		index = 待分割文本.find_first_of(用作分割的文本, start);
	}
	if (待分割文本.substr(start) != L"")
	{
		返回文本.push_back(待分割文本.substr(start));
	}
	if (要返回的子文本数目 != -1 && 要返回的子文本数目 <= 返回文本.size())
	{
		返回文本.resize(要返回的子文本数目);
	}
	return 返回文本;
}

