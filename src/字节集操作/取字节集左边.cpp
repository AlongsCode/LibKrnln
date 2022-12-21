#include"vector"
using namespace std;
//vector<unsigned char>



/*
返回一个字节集，其中包含指定字节集中从左边算起指定数量的字节
<int> 类型变量 <欲取出字节的数目>

*/
KrnlnApi vector<unsigned char> 取字节集左边(const vector<unsigned char>& 欲取其部分的字节集, size_t 欲取出字节的数目) {
	if (欲取其部分的字节集.size() == 0 || 欲取其部分的字节集.empty()) {
		return vector<unsigned char>();
	}
	if (欲取出字节的数目 <= 0) {

		return vector<unsigned char>();
	}
	if (欲取出字节的数目 > 欲取其部分的字节集.size()) {
		欲取出字节的数目 = 欲取其部分的字节集.size();

	}
	return vector<unsigned char>(欲取其部分的字节集.data(), 欲取其部分的字节集.data() + 欲取出字节的数目);

}
