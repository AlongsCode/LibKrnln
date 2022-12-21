#include<vector>
#include<algorithm>
KrnlnApi std::vector<unsigned char> 取重复字节集(size_t 重复次数, const std::vector<unsigned char>& 待重复的字节集)
{
	if (重复次数 <= 0 || 待重复的字节集.empty())
	{
		return {};
	}
	std::vector<unsigned char> buffer(待重复的字节集.size() * 重复次数);
	for (size_t i = 0; i < 重复次数; ++i)
	{
		std::copy(待重复的字节集.begin(), 待重复的字节集.end(), buffer.begin() + i * 待重复的字节集.size());
	}
	return buffer;
}

//KrnlnApi std::vector<unsigned char> 取重复字节集(size_t 重复次数, const std::vector<unsigned char>& 待重复的字节集) {
//
//	if (重复次数 <= 0 || 待重复的字节集.empty())
//		return {};
//	size_t nLen = 待重复的字节集.size();
//	if (nLen == 0)return {};
//
//	const unsigned char* pSrc = 待重复的字节集.data();
//	size_t nBuf = nLen * 重复次数;
//	unsigned char* pData = new unsigned char[nBuf];
//	if (!pData)
//	{
//		return {};
//	}
//	unsigned char* pDest = pData;
//	for (size_t i = 0; i < 重复次数; i++)
//	{
//		memcpy(pDest, pSrc, nLen);//pushaback不如原始数组操作速度快
//		pDest += nLen;
//	}
//	std::vector<unsigned char> 返回值(pData, pData + nBuf);
//	delete[]pData;
//	return 返回值;
//}