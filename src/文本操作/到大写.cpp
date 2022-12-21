#include<string>
#include <algorithm>
using namespace std;
KrnlnApi string 到大写(const string& 欲变换的文本) {
	string 返回文本(欲变换的文本);
	std::transform(欲变换的文本.begin(), 欲变换的文本.end(), 返回文本.begin(), toupper);
	return 返回文本;
}

KrnlnApi wstring 到大写(const wstring& 欲变换的文本) {
	wstring 返回文本(欲变换的文本);
	transform(欲变换的文本.begin(), 欲变换的文本.end(), 返回文本.begin(), toupper);
	return 返回文本;
}