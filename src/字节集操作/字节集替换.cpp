#include<vector>

using namespace std;
// 改自七号
KrnlnApi vector<unsigned char> 字节集替换(const vector<unsigned char>& 欲替换其部分的字节集, size_t 起始替换位置, size_t 替换长度, const vector<unsigned char>& 用作替换的字节集)
{

	if (欲替换其部分的字节集.empty())
		return {};
	const unsigned char* pBin = 欲替换其部分的字节集.data();
	const unsigned char* pSubBin = 用作替换的字节集.data();
	vector<unsigned char> ret;
	size_t nSubLen;
	size_t nLen = 欲替换其部分的字节集.size();
	if (用作替换的字节集.empty())
		nSubLen = 0;
	else
		nSubLen = 用作替换的字节集.size();

	size_t nRpLen = 替换长度;
	if (nRpLen < 0) nRpLen = 0;

	size_t nStart = 起始替换位置 - 1;
	if (nStart < 0)
		nStart = 0;
	else if (nStart > nLen)
		nStart = nLen - 1;

	// 新长度 = 源长度 - 替换长度 + 子串长度
	// 起始点 + 替换长度 <= 源长度
	if (nStart + nRpLen > nLen) nRpLen = nLen - nStart;
	if (nLen - nRpLen + nSubLen <= 0) return {};
	size_t nNewLen = nLen - nRpLen + nSubLen;


	unsigned char* pRetn;
	unsigned char* pTemp;
	if (nStart == 0) // 往前拼接
	{
		if (nSubLen == 0) // 子串为空
			return vector<unsigned char>(pBin + nRpLen, pBin + nRpLen + nNewLen);

		pRetn = new unsigned char[nNewLen];
		pTemp = pRetn;
		memcpy(pTemp, pSubBin, nSubLen);
		memcpy(pTemp + nSubLen, pBin + nRpLen, nLen - nRpLen);
		ret = vector<unsigned char>(pRetn, pRetn + nNewLen);
		delete[]pRetn;
		return ret;
	}
	else if (nStart >= nLen) // 往后拼接
	{
		if (nSubLen == 0) // 子串为空
			return  vector<unsigned char>(pBin, pBin + nNewLen);

		pRetn = new unsigned char[nNewLen];
		pTemp = pRetn;
		memcpy(pTemp, pBin, nLen);
		memcpy(pTemp + nLen, pSubBin, nSubLen);
		ret = vector<unsigned char>(pRetn, pRetn + nNewLen);
		delete[]pRetn;
		return ret;
	}

	// 中间拼接
	pRetn = pRetn = new unsigned char[nNewLen];
	pTemp = pRetn;


	memcpy(pTemp, pBin, nStart);
	pTemp += nStart;
	if (nSubLen > 0)
	{
		memcpy(pTemp, pSubBin, nSubLen);
		pTemp += nSubLen;
	}
	if (nStart + nSubLen < nNewLen)
		memcpy(pTemp, pBin + nStart + nRpLen, nLen - nStart - nRpLen);

	ret = vector<unsigned char>(pRetn, pRetn + nNewLen);
	delete[]pRetn;
	return ret;
}