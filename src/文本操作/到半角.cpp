#define _CRT_SECURE_NO_WARNINGS
#include<string>
using namespace std;
/*是否需要??*/
//KrnlnApi bool 是否为全角字符(wchar_t c)
//{
//	return c >= 0xFF00 && c <= 0xFFEF;
//}
KrnlnApi string 到半角(const std::string& str) {
	std::string result;
	unsigned char fc;
	unsigned char lc;
	for (std::string::size_type i = 0; i < str.size(); i++) {
		fc = str[i];
		lc = str[i + 1];
		if (fc == 163)
		{
			result += (unsigned char)str[i + 1] - 128;
			i++;
			continue;
		}
		else if (fc > 163)    //汉字
		{
			result += str.substr(i, 2);
			i++;
			continue;
		}
		else if (fc == 161 && lc == 161)    ///处理全角空格
		{
			result += "";
			i++;
		}
		else {
			result += str.substr(i, 1);
		}

	}
	return result;
}

KrnlnApi std::wstring 到半角(const std::wstring& text)
{
	if (text.empty())
		return std::wstring();

	std::wstring result;
	result.reserve(text.size());

	for (auto it = text.begin(); it != text.end(); ++it)
	{
		const size_t upChar = (size_t)*it;

		if (upChar == 0x3000)
		{
			result += L' ';
		}
		else if (upChar >= 65281 && upChar <= 65374)
		{
			result += (wchar_t)(upChar - 65248);
		}
		else
		{
			result += *it;
		}
	}

	return result;
}

