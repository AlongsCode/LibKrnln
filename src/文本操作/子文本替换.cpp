#include"string"
#include<limits>
using namespace std;

intptr_t  文本_子文本替换辅助(const char* str1, const char* str2)
{
	const char* cp = str1;
	const char* s1, * s2;
	while (*cp)
	{
		s1 = cp;
		s2 = str2;
		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;
		if (!*s2)
			return cp - str1;

		if (*cp < 0)
		{
			cp++;
			if (!*cp)
				return -1;
		}
		cp++;
	}
	return -1;
}

intptr_t  文本_子文本替换辅助(const wchar_t* str1, const wchar_t* str2)
{
	const wchar_t* cp = str1;
	const wchar_t* s1, * s2;
	while (*cp)
	{
		s1 = cp;
		s2 = str2;
		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;
		if (!*s2)
			return cp - str1;

		if (*cp < 0)
		{
			cp++;
			if (!*cp)
				return -1;
		}
		cp++;
	}
	return -1;
}

/*
返回一个文本，该文本中指定的子文本已被替换成另一子文本，并且替换发生的次数也是被指定的
<bool> 类型变量 <是否区分大小写> 为真区分大小写，为假不区分

*/
KrnlnApi string 子文本替换(const string& 欲被替换的文本, const string& 欲被替换的子文本, const string& 用作替换的子文本, size_t 进行替换的起始位置, size_t 替换进行的次数, bool 是否区分大小写) {// 被封七号 改
	if (欲被替换的子文本.empty())
	{
		return 欲被替换的文本;

	}
	const char* 欲被替换的子文本_ = 欲被替换的子文本.c_str();
	//开始替换位置
	size_t 起始位置 = 进行替换的起始位置;
	if (起始位置 <= 1)
		起始位置 = 0;
	else
		起始位置 = 进行替换的起始位置 - 1;
	//判断开始位置
	if (欲被替换的子文本.empty())
	{
		return 欲被替换的文本;

	}
	const char* cp = 欲被替换的文本.c_str();
	const char* pstart = cp + 起始位置;
	for (; *cp && cp < pstart; cp++)
		if (*cp < 0) cp++; // 汉字

	size_t nSlen = (cp + strlen(cp)) - 欲被替换的文本.c_str();

	//待搜索文本

	size_t ndlen = 0;
	if (欲被替换的子文本.empty()) {
		ndlen = 欲被替换的子文本.size();
	};
	//替换次数

	size_t 替换进行次数 = 替换进行的次数;
	if (替换进行次数 == -1) {
		替换进行次数 = numeric_limits<size_t>::max();// 最大替换次数21亿
	}
	size_t nSublen = 用作替换的子文本.size();

	// 开始计算
	string 返回值;
	intptr_t nPos;
	const char* pFirst = cp;
	const char* pLast = cp + nSlen;

	if (是否区分大小写) // 区分大小写
	{
		for (; 替换进行次数 > 0; 替换进行次数--)
		{

			nPos = 文本_子文本替换辅助(cp, 欲被替换的子文本_);

			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0) {
				返回值.append(pFirst, cp + nPos - pFirst);
			}
			if (nSublen > 0) {
				返回值 = 返回值 + 用作替换的子文本;

			}
			cp += nPos + ndlen;
			pFirst = cp;
		}
	}
	else
	{
		for (; 替换进行次数 > 0; 替换进行次数--)
		{
			nPos = 文本_子文本替换辅助(cp, 欲被替换的子文本_);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				返回值.append(pFirst, cp + nPos - pFirst);

			if (nSublen > 0)
				返回值 = 返回值 + 用作替换的子文本;

			cp += nPos + ndlen;
			pFirst = cp;
		}
	}

	if (pLast - pFirst > 0)
		返回值.append(pFirst, pLast - pFirst);

	// 复制计算结果
	return 返回值;
}

KrnlnApi wstring 子文本替换(const  wstring& 欲被替换的文本, const  wstring& 欲被替换的子文本, const  wstring& 用作替换的子文本, size_t 进行替换的起始位置, size_t 替换进行的次数, bool 是否区分大小写) {// 被封七号 改
	if (欲被替换的子文本.empty())
	{
		return 欲被替换的文本;

	}
	const wchar_t* 欲被替换的子文本_ = 欲被替换的子文本.c_str();
	//开始替换位置
	size_t 起始位置 = 进行替换的起始位置;
	if (起始位置 <= 1)
		起始位置 = 0;
	else
		起始位置 = 进行替换的起始位置 - 1;
	//判断开始位置
	if (欲被替换的子文本.empty())
	{
		return 欲被替换的文本;

	}
	const wchar_t* cp = 欲被替换的文本.c_str();
	const wchar_t* pstart = cp + 起始位置;
	for (; *cp && cp < pstart; cp++)
		if (*cp < 0) cp++; // 汉字

	size_t nSlen = (cp + wcslen(cp)) - 欲被替换的文本.c_str();

	size_t ndlen = 0;
	if (欲被替换的子文本.empty()) {
		ndlen = 欲被替换的子文本.size();
	};
	//替换次数

	size_t 替换进行次数 = 替换进行的次数;
	if (替换进行次数 == -1) {
		替换进行次数 = numeric_limits<size_t>::max();// 最大替换次数21亿
	}
	size_t nSublen = 用作替换的子文本.size();

	// 开始计算
	wstring 返回值;
	intptr_t nPos;
	const wchar_t* pFirst = cp;
	const wchar_t* pLast = cp + nSlen;

	if (是否区分大小写) // 区分大小写
	{
		for (; 替换进行次数 > 0; 替换进行次数--)
		{

			nPos = 文本_子文本替换辅助(cp, 欲被替换的子文本_);

			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0) {
				返回值.append(pFirst, cp + nPos - pFirst);
			}
			if (nSublen > 0) {
				返回值 = 返回值 + 用作替换的子文本;

			}
			cp += nPos + ndlen;
			pFirst = cp;
		}
	}
	else
	{
		for (; 替换进行次数 > 0; 替换进行次数--)
		{
			nPos = 文本_子文本替换辅助(cp, 欲被替换的子文本_);
			if (nPos == -1)
				break;
			if (cp + nPos - pFirst > 0)
				返回值.append(pFirst, cp + nPos - pFirst);

			if (nSublen > 0)
				返回值 = 返回值 + 用作替换的子文本;

			cp += nPos + ndlen;
			pFirst = cp;
		}
	}

	if (pLast - pFirst > 0)
		返回值.append(pFirst, pLast - pFirst);

	// 复制计算结果
	return 返回值;
}



/*尝试新算法替换七号的代码*/

#include <optional>
#include <algorithm>
std::string replace_substring(std::string text, std::string to_replace, std::optional<std::string> replace_with = std::nullopt, std::optional<size_t> start_pos = std::nullopt, std::optional<size_t> replace_count = std::nullopt, std::optional<bool> case_sensitive = std::nullopt) {
	// Get the start position for search
	size_t search_start = start_pos.value_or(0);
	// Get the replace count
	size_t count = replace_count.value_or(std::numeric_limits<size_t>::max());
	// Get the case sensitivity
	bool sensitive = case_sensitive.value_or(true);
	// Get the string to replace with
	std::string replace = replace_with.value_or("");


	if (!sensitive) {
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		std::transform(to_replace.begin(), to_replace.end(), to_replace.begin(), ::tolower);
	}

	size_t pos = text.find(to_replace, search_start);
	while (pos != std::string::npos && count > 0) {
		text.replace(pos, to_replace.length(), replace);
		pos = text.find(to_replace, pos + replace.length());
		--count;
	}

	return text;
}