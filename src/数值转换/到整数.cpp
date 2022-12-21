#include<string>


//INT 到整数(int 待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//INT 到整数(SHORT 待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//INT 到整数(BYTE 待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//INT 到整数(FLOAT 待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = (INT)待转换的文本或数值;
//	return nRet;
//
//}
//INT 到整数(double  待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = (INT)待转换的文本或数值;
//	return nRet;
//}
//INT 到整数(INT64  待转换的文本或数值) {
//	INT nRet = 0;
//	nRet = (INT)待转换的文本或数值;
//	return nRet;
//}
//INT 到整数(bool 待转换的文本或数值) {
//	return int(待转换的文本或数值);
//}
//INT 到整数(void* 待转换的文本或数值) {
//
//	INT nRet = 0;
//	nRet = (INT)待转换的文本或数值;
//	return nRet;
//
//};
KrnlnApi int 到整数(const std::wstring& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return _wtoi(待转换的文本或数值.c_str());
}


KrnlnApi int 到整数(const std::string& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return atoi(待转换的文本或数值.c_str());
}
