#include"vector"




// 调用格式： 〈整数型〉 取字节集内整数 （字节集 待处理的字节集，整数型 欲获取整数所处偏移，［逻辑型 是否反转字节序］） - 系统核心支持库->字节集操作
// 英文名称：GetIntInsideBin
// 返回字节集中所指定位置处的整数。本命令为初级命令。
// 参数<1>的名称为“待处理的字节集”，类型为“字节集（bin）”。提供待处理的字节集。
// 参数<2>的名称为“欲获取整数所处偏移”，类型为“整数型（int）”。提供所欲获取的整数值在字节集中的偏移位置。
// 参数<3>的名称为“是否反转字节序”，类型为“逻辑型（bool）”，可以被省略。指定是否将所获取整数值的字节序进行反转,譬如十六进制整数0x12345678,反转后将为0x78563412. 本功能在与类似Java这样的语言进行数据交互时很有用处. 如果参数被省略，默认值为假.
// 
// 操作系统需求： Windows、Linux
KrnlnApi int 取字节集内整数(const std::vector<unsigned char>& 待处理的字节集, size_t 欲获取整数所处偏移, bool 是否反转字节序) {
	const unsigned char* pSrc = 待处理的字节集.data();
	if (!pSrc) {
		return 0;
	}
	size_t nLen = 待处理的字节集.size();
	size_t off = 欲获取整数所处偏移;
	if (nLen - off < 0) {
		return 0;
	}
	int nValue = *(int*)(pSrc + off);
	if (是否反转字节序)
	{
		unsigned int nTmp = (unsigned int)nValue;
		nValue = nTmp >> 24;
		nValue |= ((nTmp & 0x00FF0000) >> 8);
		nValue |= ((nTmp & 0x0000FF00) << 8);
		nValue |= ((nTmp & 0x000000FF) << 24);
	}
	return nValue;
}