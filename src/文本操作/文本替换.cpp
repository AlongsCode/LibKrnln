#include"string"
using namespace std;

KrnlnApi string 文本替换(const string& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const string& 用作替换的文本) {

	if (欲被替换的文本.empty()) {
		return "";
	}
	if (替换长度 < 1) {
		return 欲被替换的文本;
	}
	size_t len_x = 欲被替换的文本.size();
	if (起始替换位置 < 1) {
		起始替换位置 = 1;
	}
	if (起始替换位置 > len_x) {
		return 欲被替换的文本;
	}
	string temp1 = 欲被替换的文本.substr(0, 起始替换位置 - 1);
	string temp2 = 欲被替换的文本.substr(欲被替换的文本.size() - (len_x - (起始替换位置 + 替换长度) + 1));
	return temp1 + 用作替换的文本 + temp2;
}

KrnlnApi string 文本替换下标(const string& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const string& 用作替换的文本) {

	if (欲被替换的文本.empty()) {
		return "";
	}
	if (替换长度 < 1) {
		return 欲被替换的文本;
	}
	size_t len_x = 欲被替换的文本.size();
	if (起始替换位置 < 0) {
		起始替换位置 = 0;
	}
	if (起始替换位置 > len_x - 1) {
		return 欲被替换的文本;
	}
	string  temp1 = 欲被替换的文本.substr(0, 起始替换位置);
	string temp2 = 欲被替换的文本.substr(欲被替换的文本.size() - (len_x - (起始替换位置 + 替换长度)));
	return temp1 + 用作替换的文本 + temp2;
}
KrnlnApi wstring 文本替换下标(const wstring& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const wstring& 用作替换的文本) {

	if (欲被替换的文本.empty()) {
		return L"";
	}
	if (替换长度 < 1) {
		return 欲被替换的文本;
	}
	size_t len_x = 欲被替换的文本.size();
	if (起始替换位置 < 0) {
		起始替换位置 = 0;
	}
	if (起始替换位置 > len_x - 1) {
		return 欲被替换的文本;
	}
	wstring  temp1 = 欲被替换的文本.substr(0, 起始替换位置);
	wstring temp2 = 欲被替换的文本.substr(欲被替换的文本.size() - (len_x - (起始替换位置 + 替换长度)));
	return temp1 + 用作替换的文本 + temp2;
}
KrnlnApi wstring 文本替换(const std::wstring& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const std::wstring& 用作替换的文本) {

	if (欲被替换的文本.empty()) {
		return L"";
	}
	if (替换长度 < 1) {
		return 欲被替换的文本;
	}
	size_t len_x = 欲被替换的文本.size();
	if (起始替换位置 < 1) {
		起始替换位置 = 1;
	}
	if (起始替换位置 > len_x) {
		return 欲被替换的文本;
	}
	wstring temp1 = 欲被替换的文本.substr(0, 起始替换位置 - 1);
	wstring temp2 = 欲被替换的文本.substr(欲被替换的文本.size() - (len_x - (起始替换位置 + 替换长度) + 1));
	return temp1 + 用作替换的文本 + temp2;
}
