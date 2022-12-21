#include<string>
#include<vector>
#include <iomanip>
#include <sstream>
#include<ctime>
#include"文本转换.h"
using namespace std;

void formatDate(std::string& strValue, const std::tm& dt, bool bOnlyDatePart = false)
{
	std::tm st = dt;

	std::stringstream strFormat;
	strFormat.imbue(std::locale("zh_CN.UTF-8"));
	strFormat << std::put_time(&st, "%Y年%m月%d日");

	if (!bOnlyDatePart) {
		if (st.tm_sec)
			strFormat << std::put_time(&st, "%H时%M分%S秒");
		else if (st.tm_min && st.tm_sec == 0)
			strFormat << std::put_time(&st, "%H时%M分");
		else if (st.tm_hour && st.tm_min == 0 && st.tm_sec == 0)
			strFormat << std::put_time(&st, "%H时");
	}

	strValue = strFormat.str();
}

void formatDate(std::wstring& strValue, const std::tm& dt, bool bOnlyDatePart = false)
{
	std::tm st = dt;
	std::wstringstream strFormat;
	strFormat << std::put_time(&st, L"%Y年%m月%d日");
	if (!bOnlyDatePart) {
		if (st.tm_sec)
			strFormat << std::put_time(&st, L"%H时%M分%S秒");
		else if (st.tm_min && st.tm_sec == 0)
			strFormat << std::put_time(&st, L"%H时%M分");
		else if (st.tm_hour && st.tm_min == 0 && st.tm_sec == 0)
			strFormat << std::put_time(&st, L"%H时");
	}
	strValue = strFormat.str();
}






#pragma region A码处理部分
//基础编码转换w2a
KrnlnApi string to_string(const wstring& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return "";
	}
	return 宽文本到文本(待转换的数据);
}

//char数组,末尾添加结束符后本质与string相同
KrnlnApi string to_string(const vector <char>& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return "";
	}
	string ret(待转换的数据.data());
	return ret;
}

//wchar数组,末尾添加结束符后本质与wstring相同到string用winApi转换即可
KrnlnApi string to_string(const vector <wchar_t>& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return "";
	}
	wstring ret(待转换的数据.data());
	return 宽文本到文本(ret);
}

//构造函数数组
KrnlnApi string to_string(const char* 待转换的数据) {
	if (待转换的数据)
	{
		return string();
	}
	return 待转换的数据;
}

//编码转换
KrnlnApi string to_string(const wchar_t* 待转换的数据) {
	if (待转换的数据)
	{
		return 宽文本到文本(待转换的数据);
	}
	return string();
}




//字节集
KrnlnApi string to_string(const vector<unsigned char>& 待转换的数据) {
	if (待转换的数据.size() == 0) {
		return "";
	}
	string 返回文本;
	返回文本.append((char*)待转换的数据.data(), 待转换的数据.size() / sizeof(char));
	return 返回文本.c_str();
}
KrnlnApi std::string to_string(const string& 待转换的数据) {
	return 待转换的数据;
};
//std::tm
KrnlnApi std::string to_string(const std::tm& dt) {
	std::string strValue;
	formatDate(strValue, dt);
	return strValue;
}
#pragma endregion A码处理部分


#pragma region W码处理部分
//基础编码转换A2W
KrnlnApi wstring to_wstring(const string& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return L"";
	}
	return 文本到宽文本(待转换的数据);
}
KrnlnApi wstring to_wstring(const wstring& 待转换的数据) {

	return 待转换的数据;
}
//char数组,末尾添加结束符后本质与string相同
KrnlnApi wstring to_wstring(const vector <char>& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return L"";
	}
	string ret(待转换的数据.data());
	return 文本到宽文本(ret);
}

//wchar数组,末尾添加结束符后本质与wstring相同到string用winApi转换即可
KrnlnApi wstring to_wstring(const vector <wchar_t>& 待转换的数据) {
	if (待转换的数据.empty())
	{
		return L"";
	}
	wstring ret(待转换的数据.data());
	return ret;
}

//构造函数数组
KrnlnApi wstring to_wstring(const char* 待转换的数据) {
	if (!待转换的数据)
	{
		return wstring();
	}

	return 文本到宽文本(待转换的数据);
}

//编码转换
KrnlnApi wstring to_wstring(const wchar_t* 待转换的数据) {
	if (!待转换的数据)
	{
		return wstring();
	}
	return 待转换的数据;
}


//字节集
KrnlnApi wstring to_wstring(const vector<unsigned char>& 待转换的数据) {
	if (待转换的数据.size() == 0) {
		return L"";
	}
	wstring 返回文本;
	返回文本.append((wchar_t*)待转换的数据.data(), 待转换的数据.size() / sizeof(wchar_t));
	return 返回文本.c_str();
}

//
KrnlnApi std::wstring to_wstring(const std::tm& dt) {
	std::wstring strValue;
	formatDate(strValue, dt);
	return strValue;
}

#pragma endregion W码处理部分