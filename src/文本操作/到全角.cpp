#include<string>
using namespace std;


KrnlnApi string 到全角(const std::string& s) {
	string ret;
	if (!s.empty()) {
		for (size_t i = 0; i < s.size(); i++)//对于ansi处理，中文要判断前后字符，尽量不要使用迭代器。
		{
			if (s[i] == '~') {
				ret += "～";
			}
			else if (std::isspace(s[i])) {
				ret += "　";
			}
			else if (s[i] <= 0x20 || s[i] >= 0x7F) {
				if (s[i] & 0x80) { // 中文字符
					if (!s[i + 1]) { // 结束符截断
						ret += '\0';
						return ret;
					}
					ret += s.substr(i, 2);
					i++;
				}
				else { // 常规字符
					ret += s[i];
				}
			}
			else {
				ret += (char)163; // 中文两个字符中的高位
				ret += s[i] | (char)0x80; // 低位
			}
		}

	}
	return ret;
}
KrnlnApi std::wstring 到全角(const std::wstring& s)
{
	std::wstring result;
	if (!s.empty()) {
		result.reserve(s.size());//宽字符win下2，linux3为固定，可以提前申请，防止每次拼接时申请内存,string不可以是因为汉字为两字符
		for (const auto& c : s)
		{
			if (c == ' ')
			{
				result += (wchar_t)0x3000;
			}
			else if (c >= 33 && c <= 126)
			{
				result += (wchar_t)(c + 65248);
			}
			else
			{
				result += c;
			}
		}
	}
	return result;
}