#include"string"
#include <algorithm>
using namespace std;
KrnlnApi string 到小写(const  string& 欲变换的文本) {
	string Ret(欲变换的文本);
	std::transform(欲变换的文本.begin(), 欲变换的文本.end(), Ret.begin(), tolower);
	return  Ret;
}
KrnlnApi wstring 到小写(const wstring& 欲变换的文本) {
	wstring Ret(欲变换的文本);
	std::transform(欲变换的文本.begin(), 欲变换的文本.end(), Ret.begin(), tolower);
	return  Ret;
}