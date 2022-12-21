#include<string>




//double 到数值 (unsigned char 待转换的文本或数值) {
//	INT nVal = 待转换的文本或数值;
//	return nVal;
//}
//double 到数值(SHORT 待转换的文本或数值) {
//	INT nVal = 待转换的文本或数值;
//	return nVal;
//}
//double 到数值(double 待转换的文本或数值) {
//
//	
//	return 待转换的文本或数值;
//	//ArgInf.m_double = strtod(ArgInf.m_pText,NULL);
//}
//double 到数值(FLOAT 待转换的文本或数值) {
//	FLOAT floatval = 待转换的文本或数值;
//	double ret;
//	ret = floatval;
//	return ret;
//}
//double 到数值(INT64 待转换的文本或数值) {
//	INT64 int64 = 待转换的文本或数值;
//	double ret;
//	ret = (DOUBLE)int64;
//	return ret;
//}
KrnlnApi double 到数值(const std::string& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return strtod(待转换的文本或数值.c_str(), NULL);
}


KrnlnApi double 到数值(const std::wstring& 待转换的文本或数值) {
	if (待转换的文本或数值.empty())
	{
		return 0;
	}
	return wcstod(待转换的文本或数值.c_str(), NULL);
}