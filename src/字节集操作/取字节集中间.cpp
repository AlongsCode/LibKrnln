#include"vector"
using namespace std;
//vector<unsigned char>
/*
返回一个字节集，其中包含指定字节集中从指定位置算起指定数量的字节
<int> 类型变量 <欲取出字节的数目>

*/
KrnlnApi vector<unsigned char>  取字节集中间(const vector<unsigned char>& 欲取其部分的字节集, size_t 起始取出位置, size_t 欲取出字节的数目) {
	size_t nDataSize = 欲取其部分的字节集.size();
	size_t nObjLen = 欲取出字节的数目;
	if (nDataSize == 0 || nObjLen <= 0) {
		return {};
	}
	size_t nStart = 起始取出位置;
	if (nStart <= 0) {
		nStart = 1;
	}
	if (nStart - 1 > nDataSize) {
		return {};
	}
	return vector<unsigned char>(欲取其部分的字节集.data() + 起始取出位置 - 1, (欲取其部分的字节集.data() + 起始取出位置 - 1) + nDataSize);
}