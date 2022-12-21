
#include<string>
//
//
//short 到短整数(int 待转换的文本或数值) {
//	short nRet = 0;
//	nRet = (short)待转换的文本或数值;
//	return nRet;
//
//}
//short 到短整数(short 待转换的文本或数值) {
//
//	return 待转换的文本或数值;
//
//}
//short 到短整数(unsigned char 待转换的文本或数值) {
//	return (short)待转换的文本或数值;
//}
//short 到短整数(float 待转换的文本或数值) {
//
//	return (short)待转换的文本或数值;
//
//}
//short 到短整数(double  待转换的文本或数值) {
//	return (short)待转换的文本或数值;
//}
//short 到短整数(long long  待转换的文本或数值) {
//
//	return (short)待转换的文本或数值;
//}
//

KrnlnApi short 到短整数(const std::string& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return (short)atoi(待转换的文本或数值.c_str());
}

KrnlnApi short 到短整数(const std::wstring& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return (short)_wtoi(待转换的文本或数值.c_str());
}
