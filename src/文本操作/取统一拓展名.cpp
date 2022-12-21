#include<string>
#include <algorithm>
using namespace std;
KrnlnApi string 取统一拓展名(const std::string& str)
{
	string result(str);
	std::transform(str.begin(), str.end(), result.begin(), tolower);
	if (!result.empty())
	{
		result = result.substr(result.rfind(".") + 1);
	}
	return result;
}
KrnlnApi wstring 取统一拓展名(const  wstring& str)
{
	wstring result(str);
	std::transform(str.begin(), str.end(), result.begin(), tolower);
	if (!result.empty())
	{
		result = result.substr(result.rfind(L".") + 1);
	}
	return result;
}