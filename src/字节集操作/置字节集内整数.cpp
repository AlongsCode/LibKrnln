
#include"vector"
using namespace std;
//vector<unsigned char>


/*
设置字节集中所指定位置处的整数值
<bool> 类型变量 <是否反转字节序> 指定是否将所设置整数的字节序进行反转,譬如十六进制整数0x12345678,反转后将为0x78563412. 本功能在与类似Java这样的语言进行数据交互时很有用处. 如果参数被省略，默认值为假.

*/
KrnlnApi void 置字节集内整数(vector<unsigned char> 待处理的字节集, size_t 欲设置整数所处偏移, int 欲设置的整数值, bool 是否反转字节序) {


	unsigned char* pSrc = 待处理的字节集.data();
	if (!pSrc) return;

	size_t nLen = 待处理的字节集.size();
	size_t off = 欲设置整数所处偏移;
	if (nLen - off < 0) return;

	int nValue = 欲设置的整数值;
	if (是否反转字节序)
	{
		int nTmp = nValue;
		nValue = nTmp >> 24;
		nValue |= ((nTmp & 0x00FF0000) >> 8);
		nValue |= ((nTmp & 0x0000FF00) << 8);
		nValue |= ((nTmp & 0x000000FF) << 24);
	}
	*(unsigned char*)(pSrc + off) = nValue;
}