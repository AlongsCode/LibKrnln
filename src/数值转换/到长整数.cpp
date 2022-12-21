#include<string>



////INT64 到长整数(int 待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = 待转换的文本或数值;
////	return nRet;
////
////}
////INT64 到长整数(SHORT 待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = 待转换的文本或数值;
////	return nRet;
////
////}
////INT64 到长整数(BYTE 待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = 待转换的文本或数值;
////	return nRet;
////
////}
////INT64 到长整数(FLOAT 待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = (INT64)待转换的文本或数值;
////	return nRet;
////
////}
////INT64 到长整数(double  待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = (INT64)待转换的文本或数值;
////	return nRet;
////}
////INT64 到长整数(INT64  待转换的文本或数值) {
////	INT64 nRet = 0;
////	nRet = 待转换的文本或数值;
////	return nRet;
////}
//
//#define IS_NUMBER_CHAR(ch)  ((intptr_t)(ch) >= (intptr_t)'0' && (intptr_t)(ch) <= (intptr_t)'9')
//INT64 StrToN64(const wchar_t* ps)
//{
//
//
//	// 跳过空白
//	while (*ps != '\0' && (DWORD)*ps <= (DWORD)' ')
//		ps++;
//
//	// 跳过空白后遇到了文本结束符?
//	if (*ps == '\0')
//		return 0;
//
//	// 获取数值符号
//	bool blpNeg;  // 记录是否为负数
//	if (*ps == '-')
//	{
//		blpNeg = TRUE;
//		ps++;
//	}
//	else
//	{
//		blpNeg = FALSE;
//
//		if (*ps == '+')
//			ps++;
//	}
//
//	// 用作计算是否溢出时使用
//	const UINT64 c_ui64Cutoff = UINT64_MAX / (UINT64)10;
//	const DWORD c_dwCutlim = (DWORD)(UINT64_MAX % (UINT64)10);
//
//	// 用作记录所获得的值
//	UINT64 u64Value = 0;
//
//	// 转换每个字符
//	DWORD c = (DWORD)*ps;
//	while (IS_NUMBER_CHAR(c))  // 为数字?
//	{
//		c -= '0';
//
//		if (u64Value > c_ui64Cutoff || (u64Value == c_ui64Cutoff && c > c_dwCutlim))  // 检查是否会导致溢出UINT64
//			return (blpNeg ? INT64_MIN : INT64_MAX);  // 如果溢出则直接返回
//
//		// 加入该数值
//		u64Value *= (UINT64)10;
//		u64Value += (UINT64)c;
//
//		// 去处理下一个数字
//		ps++;
//		c = *ps;
//	}
//
//	if (blpNeg)
//		return (((INT64)u64Value) < 0 ? INT64_MIN : -((INT64)u64Value));
//	else
//		return (u64Value > INT64_MAX ? INT64_MAX : ((INT64)u64Value));
//}
//
//
//
//INT64 到长整数(const char* 待转换的文本或数值) {
//	INT64 nRet = 0;
//
//	if (待转换的文本或数值)
//	{
//		nRet = _atoi64(待转换的文本或数值);
//
//	}
//	return nRet;
//}
//
//INT64 到长整数(const wchar_t* 待转换的文本或数值) {
//	INT64 nRet = 0;
//
//	if (待转换的文本或数值)
//	{
//		std::wstring num(待转换的文本或数值);
//
//		nRet = _wtoi64(num.c_str());
//
//	}
//	return nRet;
//}
//
//INT64 到长整数(bool 待转换的文本或数值) {
//	if (待转换的文本或数值) {
//		return 1;
//	}
//	return 0;
//}
//
//INT64 到长整数(void* 待转换的文本或数值) {
//	INT64 nRet = 0;
//	nRet = (INT64)待转换的文本或数值;
//	return nRet;
//}



KrnlnApi long long 到长整数(const std::wstring& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return _wtoi64(待转换的文本或数值.c_str());
}
KrnlnApi long long 到长整数(const std::string& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return _atoi64(待转换的文本或数值.c_str());
}