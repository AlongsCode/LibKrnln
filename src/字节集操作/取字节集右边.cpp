#include"vector"
using namespace std;





/*
返回一个字节集，其中包含指定字节集中从右边算起指定数量的字节
<int> 类型变量 <欲取出字节的数目>
*/
KrnlnApi vector<unsigned char> 取字节集右边(const vector<unsigned char>& 欲取其部分的字节集, size_t 欲取出字节的数目) {
	if (欲取其部分的字节集.empty()) {
		return {};
	}
	size_t nDataSize = 欲取其部分的字节集.size();
	if (nDataSize == 0 || 欲取出字节的数目 <= 0) {
		return  {};
	}
	size_t nOffset = nDataSize - 欲取出字节的数目;
	if (nOffset < 0) {
		nOffset = 0;
	}
	nDataSize = 欲取出字节的数目;
	if (nDataSize > 欲取其部分的字节集.size()) {
		nDataSize = 欲取其部分的字节集.size();
	}
	return vector<unsigned char>((欲取其部分的字节集.data() + nOffset), (欲取其部分的字节集.data() + nOffset) + nDataSize);
}
