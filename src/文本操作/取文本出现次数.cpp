#include<string>


KrnlnApi size_t 取文本出现次数(const std::string& str, const std::string& text) {
	size_t count = 0;
	size_t pos = str.find(text, 0);
	while (pos != std::string::npos) {
		count++;
		pos = str.find(text, pos + text.length());
	}
	return count;
}

KrnlnApi size_t 取文本出现次数(const std::wstring& str, const std::wstring& text) {
	size_t count = 0;
	size_t pos = str.find(text, 0);
	while (pos != std::string::npos) {
		count++;
		pos = str.find(text, pos + text.length());
	}
	return count;
}