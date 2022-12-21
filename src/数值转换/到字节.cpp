#include<string>
KrnlnApi unsigned char 到字节(const std::string& 待转换的文本或数值) {

	if (待转换的文本或数值.empty())  return 0;
	return *(unsigned char*)待转换的文本或数值.c_str();
}

KrnlnApi unsigned char 到字节(const std::wstring& 待转换的文本或数值) {

	if (待转换的文本或数值.empty()) return 0;
	return *(unsigned char*)待转换的文本或数值.c_str();
}
//unsigned char 到字节(int 待转换的文本或数值) {
//	return (unsigned char)待转换的文本或数值;
//}
//unsigned char 到字节(double 待转换的文本或数值) {
//	return (unsigned char)到整数(待转换的文本或数值);
//}
//unsigned char 到字节(float 待转换的文本或数值) {
//	return (unsigned char)到整数(待转换的文本或数值);
//}
//byte 到字节(unsigned char 待转换的文本或数值) {
//	return 待转换的文本或数值;
//}
//byte 到字节(bool 待转换的文本或数值) {
//	if (待转换的文本或数值) {
//		return 1;
//	}
//	return 0;
//}
//byte 到字节(short 待转换的文本或数值) {
//	return (unsigned char)待转换的文本或数值;
//}
//byte 到字节(INT64 待转换的文本或数值) {
//	return (unsigned char)待转换的文本或数值;
//}