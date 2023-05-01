#pragma once


//返回一个文本，代表指定数值、逻辑值或日期时间被转换后的结果。如果为文本数据，将被直接返回。本命令为初级命令。* | *
#pragma region 到文本(WA码)及其宏
#define 到文本A(val) to_string(val)
std::string to_string(const std::wstring& 待转换的数据);
std::string to_string(const std::vector <char>& 待转换的数据);
std::string to_string(const std::vector <wchar_t>& 待转换的数据);
std::string to_string(const char* 待转换的数据);
std::string to_string(const wchar_t* 待转换的数据);
std::string to_string(const std::vector<unsigned char>& 待转换的数据);
std::string to_string(const std::tm& 待转换的数据);
std::string to_string(const std::string& 待转换的数据);
//W码声明

#define 到文本W(val) to_wstring(val)
std::wstring to_wstring(const std::string& 待转换的数据);
std::wstring to_wstring(const std::vector <char>& 待转换的数据);
std::wstring to_wstring(const std::vector <wchar_t>& 待转换的数据);
std::wstring to_wstring(const char* 待转换的数据);
std::wstring to_wstring(const wchar_t* 待转换的数据);
std::wstring to_wstring(const std::vector<unsigned char>& 待转换的数据);
std::wstring to_wstring(const std::tm& 待转换的数据);
std::wstring to_wstring(const std::wstring& 待转换的数据);

#ifdef _UNICODE
#define 到文本(val) 到文本W(val)
#else
#define 到文本(val) 到文本A(val)
#endif
#pragma endregion 

#pragma region 到半角(WA码)及其宏
std::string 到半角(const std::string& 欲变换的文本);
std::wstring 到半角(const std::wstring& 欲变换的文本);
#pragma endregion 


#pragma region 到全角(WA码)及其宏
std::wstring  到全角(const std::wstring& 欲变换的文本);
std::string 到全角(const std::string& 欲变换的文本);
#pragma endregion 

#pragma region 到大写(WA码)及其宏
std::string 到大写(const std::string& 欲变换的文本);
std::wstring 到大写(const std::wstring& 欲变换的文本);

//#ifdef _UNICODE
//#define 到大写 到大写W
//#else
//#define 到大写 到大写A
//#endif
#pragma endregion 

#pragma region 到小写(WA码)及其宏
std::string 到小写(const std::string& 欲变换的文本);
std::wstring 到小写(const std::wstring& 欲变换的文本);

//#ifdef _UNICODE
//#define 到小写 到大写W
//#else
//#define 到小写 到大写A
//#endif
#pragma endregion 

#pragma region 倒找文本(WA码)及其宏
intptr_t 倒找文本(std::wstring 被搜寻的文本, std::wstring 欲寻找的文本, intptr_t 起始搜寻位置 = -1, bool 是否不区分大小写 = true);
intptr_t 倒找文本(std::string 被搜寻的文本, std::string 欲寻找的文本, intptr_t 起始搜寻位置 = -1, bool 是否不区分大小写 = true);

//#ifdef _UNICODE
//#define 倒找文本 倒找文本W
//#else
//#define 倒找文本 倒找文本A
//#endif
#pragma endregion 

#pragma region 分割文本(WA码)及其宏
std::vector<std::string> 分割文本(const std::string& 待分割文本, const std::string& 用作分割的文本, size_t 要返回的子文本数目 = -1);
std::vector<std::wstring> 分割文本(const std::wstring& 待分割文本, const std::wstring& 用作分割的文本, size_t 要返回的子文本数目 = -1);

//#ifdef _UNICODE
//#define 分割文本 分割文本W
//#else
//#define 分割文本 分割文本A
//#endif
#pragma endregion 

#pragma region 取代吗(WA码)
int 取代码(const std::string& 欲取字符代码的文本, size_t 欲取其代码的字符位置 = 1);
short 取代码(const std::wstring& 欲取字符代码的文本, size_t 欲取其代码的字符位置 = 1);
#pragma endregion 

#pragma region 取空白文本(WA码)及其宏
std::wstring 取空白文本W(size_t 重复次数);
std::string 取空白文本A(size_t 重复次数);

#ifdef _UNICODE
#define 取空白文本 取空白文本W
#else
#define 取空白文本 取空白文本A
#endif
#pragma endregion 

#pragma region 取文本右边(WA码)及其宏
std::string 取文本右边(const std::string& 欲取其部分的文本, size_t 欲取出字符的数目);
std::wstring 取文本右边(const std::wstring& 欲取其部分的文本, size_t 欲取出字符的数目);


#pragma endregion 

#pragma region 取文本长度(WA码)宏

size_t 取文本长度(const std::string& 文本数据);
size_t 取文本长度(const std::wstring& 文本数据);

#pragma endregion 

#pragma region 取文本中间(WA码)及其宏
std::string 取文本中间(const std::string& 欲取其部分的文本, size_t 起始取出位置, size_t 欲取出字符的数目);
std::wstring 取文本中间(const std::wstring& 欲取其部分的文本, size_t 起始取出位置, size_t 欲取出字符的数目);

//#ifdef _UNICODE
//#define 取文本中间 取文本中间W
//#else
//#define 取文本中间 取文本中间A
//#endif
#pragma endregion 

#pragma region 取文本左边(WA码)及其宏
std::wstring 取文本左边(const std::wstring& 欲取其部分的文本, size_t 欲取出字符的数目);
std::string 取文本左边(const std::string& 欲取其部分的文本, size_t 欲取出字符的数目);

//#ifdef _UNICODE
//#define 取文本左边 取文本左边W
//#else
//#define 取文本左边 取文本左边A
//#endif
#pragma endregion 


#pragma region 取重复文本(WA码)及其宏
std::string 取重复文本(size_t 重复次数, const std::string& 待重复文本);
std::wstring 取重复文本(size_t 重复次数, const std::wstring& 待重复文本);

//#ifdef _UNICODE
//#define 取重复文本 取重复文本W
//#else
//#define 取重复文本 取重复文本A
//#endif
#pragma endregion 

#pragma region 删全部空(WA码)及其宏
//给什么处理什么无需重载

std::wstring 删全部空(std::wstring 欲删除空格的文本);//宽字符
std::string 删全部空(std::string 欲删除空格的文本);//窄字符

#pragma endregion 

#pragma region 删首空(WA码)及其宏
//给什么处理什么无需重载

std::wstring 删首空(std::wstring 欲删除空格的文本);
std::string 删首空(std::string 欲删除空格的文本);
#pragma endregion 

#pragma region 删尾空(WA码)及其宏
//给什么处理什么无需重载

std::string 删尾空(std::string 欲删除空格的文本);
std::wstring 删尾空(std::wstring 欲删除空格的文本);
#pragma endregion 

#pragma region 文本比较(WA码)及其宏
//给什么处理什么无需重载

int 文本比较(const std::string& 待比较文本一, const std::string& 待比较文本二, bool 是否区分大小写);
int 文本比较(const std::wstring& 待比较文本一, const std::wstring& 待比较文本二, bool 是否区分大小写);
#pragma endregion 


#pragma region 文本到UTF-8(未完成)
//给什么处理什么无需重载

#pragma endregion 

#pragma region 文本





/*   调用格式： 〈文本型〉 文本替换 （文本型 欲被替换的文本，整数型 起始替换位置，整数型 替换长度，［文本型 用作替换的文本］） - 系统核心支持库->文本操作
	英文名称：ReplaceText
	将指定文本的某一部分用其它的文本替换。本命令为初级命令。
	参数<1>的名称为“欲被替换的文本”，类型为“文本型（text）”。
	参数<2>的名称为“起始替换位置”，类型为“整数型（int）”。替换的起始位置，1为首位置，2为第2个位置，如此类推。
	参数<3>的名称为“替换长度”，类型为“整数型（int）”。
	参数<4>的名称为“用作替换的文本”，类型为“文本型（text）”，可以被省略。如果本参数被省略，则删除文本中的指定部分。

	操作系统需求： Windows、Linux*/
std::wstring 文本替换(const std::wstring& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const std::wstring& 用作替换的文本);
/*   调用格式： 〈文本型〉 文本替换 （文本型 欲被替换的文本，整数型 起始替换位置，整数型 替换长度，［文本型 用作替换的文本］） - 系统核心支持库->文本操作
	英文名称：ReplaceText
	将指定文本的某一部分用其它的文本替换。本命令为初级命令。
	参数<1>的名称为“欲被替换的文本”，类型为“文本型（text）”。
	参数<2>的名称为“起始替换位置”，类型为“整数型（int）”。替换的起始位置，1为首位置，2为第2个位置，如此类推。
	参数<3>的名称为“替换长度”，类型为“整数型（int）”。
	参数<4>的名称为“用作替换的文本”，类型为“文本型（text）”，可以被省略。如果本参数被省略，则删除文本中的指定部分。
	操作系统需求： Windows、Linux*/
std::string 文本替换(const std::string& 欲被替换的文本, size_t 起始替换位置, size_t 替换长度, const std::string& 用作替换的文本);

std::string 文本替换下标(const std::string& 欲被替换的文本, size_t 起始替换下标, size_t 替换长度, const std::string& 用作替换的文本);
std::wstring 文本替换下标(const std::wstring& 欲被替换的文本, size_t 起始替换下标, size_t 替换长度, const std::wstring& 用作替换的文本);
#pragma endregion 


#pragma region 寻找文本
//给什么处理什么无需定义宏 重载
intptr_t 寻找文本(const std::wstring& 被搜寻的文本, const std::wstring& 欲寻找的文本, size_t 起始搜寻位置 = 0, bool 是否不区分大小写 = 1);
intptr_t 寻找文本(const std::string& 被搜寻的文本, const std::string& 欲寻找的文本, size_t 起始搜寻位置 = 0, bool 是否不区分大小写 = 1);
//返回匹配串的起始下标
intptr_t 寻找文本下标(const std::string& text, const std::string& search, size_t start_pos = 0, bool ignore_case = 1);
//返回匹配串的起始下标
intptr_t 寻找文本下标(const std::wstring& text, const std::wstring& search, size_t start_pos = 0, bool ignore_case = 1);
#pragma endregion 

#pragma region 分割文本(WA码)及其宏
std::string 指针到文本A(void* 内存文本指针);
std::wstring 指针到文本W(void* 内存文本指针);

#ifdef _UNICODE
#define 指针到文本 指针到文本W
#else
#define 指针到文本 指针到文本A
#endif
#pragma endregion 
std::string 取统一拓展名(const std::string& str);
std::wstring 取统一拓展名(const std::wstring& str);
#pragma region 子文本替换
//给什么处理什么无需定义宏 重载
std::string 子文本替换(const std::string& 欲被替换的文本, const std::string& 欲被替换的子文本, const std::string& 用作替换的子文本 = "", size_t 进行替换的起始位置 = 1, size_t 替换进行的次数 = 0, bool 是否区分大小写 = false);
std::wstring 子文本替换(const std::wstring& 欲被替换的文本, const std::wstring& 欲被替换的子文本, const std::wstring& 用作替换的子文本 = L"", size_t 进行替换的起始位置 = 1, size_t 替换进行的次数 = 0, bool 是否区分大小写 = false);
#pragma endregion 


#pragma region 字符(WA码)及其宏
std::string 字符A(char 欲取其字符的字符代码);
std::wstring 字符W(wchar_t 欲取其字符的字符代码);

#ifdef _UNICODE
#define 字符 字符W
#else
#define 字符 字符A
#endif
#pragma endregion 

bool 是否以文本结尾(const std::string& 所欲操作的文本, const std::string& 搜索字符, bool 是否区分大小写);
bool 是否以文本结尾(const std::wstring& 所欲操作的文本, const std::wstring& 搜索字符, bool 是否区分大小写);
bool 是否以文本开头(const std::string& 所欲操作的文本, const std::string& 搜索字符, bool 是否区分大小写);
bool 是否以文本开头(const std::wstring& 所欲操作的文本, const std::wstring& 搜索字符, bool 是否区分大小写);

//获取指定文本在字符串中出现的次数
size_t 取文本出现次数(const std::string& str, const std::string& text);

size_t 取文本出现次数(const std::wstring& str, const std::wstring& text);


/*通过前后文本，取出所有最短匹配要求的中间文本。*/
inline std::vector<std::string> 取中间文本(const std::string& 欲取的文本, const std::string& 左边文本, const std::string& 右边文本)
{
	std::vector<std::string> aryText;
	size_t start_place = 0;

	while (start_place != std::string::npos) {
		start_place = 欲取的文本.find(左边文本, start_place);

		if (start_place != std::string::npos) {
			start_place += 左边文本.length();

			size_t end_place = 欲取的文本.find(右边文本, start_place);

			if (end_place != std::string::npos) {
				std::string ret = 欲取的文本.substr(start_place, end_place - start_place);
				aryText.push_back(ret);
				start_place = end_place + 右边文本.length();
			}
		}
	}
	return aryText;
};
/*通过前后文本，取出所有最短匹配要求的中间文本。*/
inline std::vector<std::string> 取中间文本(const std::string& 欲取的文本, const std::string& 左边文本, const std::string& 右边文本, const size_t& 最大获取数量)
{
	std::vector<std::string> aryText;
	size_t start_place = 0;

	while (start_place != std::string::npos) {
		if (aryText.size() >= 最大获取数量)
		{
			break;
		}
		start_place = 欲取的文本.find(左边文本, start_place);

		if (start_place != std::string::npos) {
			start_place += 左边文本.length();

			size_t end_place = 欲取的文本.find(右边文本, start_place);

			if (end_place != std::string::npos) {
				std::string ret = 欲取的文本.substr(start_place, end_place - start_place);
				aryText.push_back(ret);

				start_place = end_place + 右边文本.length();
			}
		}
	}
	return aryText;
};

inline std::string 删数值文本左侧无效零(const std::string& str)
{
	std::string result = str;
	auto pos = result.find_first_not_of('0'); // 找到第一个非零字符的位置
	if (pos != std::string::npos)
	{
		result.erase(0, pos); // 删除左侧无用的零
	}
	// 如果存在小数点，则删除结尾的零和小数点
	if (auto pos_dot = result.find_last_of('.'); pos_dot != std::string::npos)
	{
		// 找到最后一个非零数字的位置
		auto pos_nonzero = result.find_last_not_of('0');
		// 如果最后一个非零数字位于小数点之前，则将小数点一起删除
		if (pos_nonzero < pos_dot)
		{
			result.erase(pos_dot, std::string::npos);
		}
		// 如果最后一个非零数字位于小数点之后，则仅删除结尾的零字符
		else
		{
			result.erase(pos_nonzero + 1, std::string::npos);
		}
	}
	return result;
}
inline std::wstring 删数值文本左侧无效零(const std::wstring& str)
{
	std::wstring result = str;
	auto pos = result.find_first_not_of(L'0'); // 找到第一个非零字符的位置
	if (pos != std::wstring::npos)
	{
		result.erase(0, pos); // 删除左侧无用的零
	}
	// 如果存在小数点，则删除结尾的零和小数点
	if (auto pos_dot = result.find_last_of(L'.'); pos_dot != std::wstring::npos)
	{
		// 找到最后一个非零数字的位置
		auto pos_nonzero = result.find_last_not_of(L'0');
		// 如果最后一个非零数字位于小数点之前，则将小数点一起删除
		if (pos_nonzero < pos_dot)
		{
			result.erase(pos_dot, std::wstring::npos);
		}
		// 如果最后一个非零数字位于小数点之后，则仅删除结尾的零字符
		else
		{
			result.erase(pos_nonzero + 1, std::wstring::npos);
		}
	}
	return result;
}