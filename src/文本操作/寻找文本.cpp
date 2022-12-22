#include<string>
#include <algorithm>


KrnlnApi intptr_t 寻找文本(const std::string& text, const std::string& search, size_t start_pos = 0, bool ignore_case = 0)
{
	if (ignore_case) {
		std::string formatted_text = text;
		std::string formatted_search = search;
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
}


KrnlnApi intptr_t 寻找文本(const std::wstring& text, const std::wstring& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		std::wstring formatted_text = text;
		std::wstring formatted_search = search;
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret + 1;
		}
		return -1;
	}
}




KrnlnApi intptr_t 寻找文本下标(const std::string& text, const std::string& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		std::string formatted_text = text;
		std::string formatted_search = search;
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret;
		}
		return -1;
	}
}


KrnlnApi intptr_t 寻找文本下标(const std::wstring& text, const std::wstring& search, size_t start_pos, bool ignore_case)
{
	if (ignore_case) {
		std::wstring formatted_text = text;
		std::wstring formatted_search = search;
		std::transform(text.begin(), text.end(), formatted_text.begin(), std::toupper);
		std::transform(search.begin(), search.end(), formatted_search.begin(), std::toupper);
		intptr_t ret = formatted_text.find(formatted_search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret;
		}
		return -1;
	}
	else {
		intptr_t ret = text.find(search.c_str(), start_pos);
		if (ret != text.npos) {
			return ret;
		}
		return -1;
	}
}



