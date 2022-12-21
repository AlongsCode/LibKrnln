#include<string>



//float 到小数(bool 待转换的文本或数值) {
//	if (待转换的文本或数值) {
//		return 1;
//	}
//	return 0;
//}
//float 到小数(INT 待转换的文本或数值) {
//	float nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//float 到小数(SHORT 待转换的文本或数值) {
//	float nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//float 到小数(unsigned char 待转换的文本或数值) {
//	float nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//float 到小数(FLOAT 待转换的文本或数值) {
//	float nRet = 0;
//	nRet = 待转换的文本或数值;
//	return nRet;
//
//}
//float 到小数(double  待转换的文本或数值) {
//	float nRet = 0;
//	nRet = (float)待转换的文本或数值;
//	return nRet;
//}
//float 到小数(INT64  待转换的文本或数值) {
//	float nRet = 0;
//	nRet = (float)待转换的文本或数值;
//	return nRet;
//}
KrnlnApi float 到小数(const std::string& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0.0f;
	}
	return strtof(待转换的文本或数值.c_str(), nullptr);//std::stof(待转换的文本或数值.c_str());stl老是出毛病
}

KrnlnApi float 到小数(const std::wstring& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0.0f;
	}
	return wcstof(待转换的文本或数值.c_str(), nullptr);
}

