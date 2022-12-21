#include<vector>
using namespace std;

// 改自被封七号
KrnlnApi size_t 寻找字节集(const vector<unsigned char>& 被搜寻的字节集, const vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置) {
	if (被搜寻的字节集.empty() || 欲寻找的字节集.empty())
		return -1;

	size_t nLen = 被搜寻的字节集.size();
	size_t nSubLen = 欲寻找的字节集.size();

	const unsigned char* pSrc;
	size_t off;
	if (起始搜寻位置 <= 1)
	{
		off = 1;
		pSrc = 被搜寻的字节集.data();
	}
	else
	{
		off = 起始搜寻位置;
		pSrc = 被搜寻的字节集.data() + off - 1;
		nLen -= off - 1;
	}

	if (nLen <= 0 || nSubLen <= 0 || nSubLen > nLen)
		return -1;

	const  unsigned char* pDes = 欲寻找的字节集.data();
	size_t i;

	// 短子串直接暴力搜索
	switch (nSubLen)
	{
	case 1:
		i = (const unsigned char*)memchr(pSrc, pDes[0], nLen) - pSrc;
		if (i >= 0)
			return i + off;
		else
			return -1;
	case 2:
		for (i = 0; i < nLen - 1; i++)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				return i + off;
		return -1;
	case 3:
		for (i = 0; i < nLen - 2; i++)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				if (pSrc[i + 2] == pDes[2])
					return i + off;
		return -1;
	case 4:
		for (i = 0; i < nLen - 3; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				return i + off;
		return -1;
	case 5:
		for (i = 0; i < nLen - 4; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (pSrc[i + 4] == pDes[4])
					return i + off;
		return -1;
	case 6:
		for (i = 0; i < nLen - 5; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (((short*)(pSrc + i + 4))[0] == ((short*)(pDes + 4))[0])
					return i + off;
		return -1;
	default:
		break;
	}
	size_t next[256];
	for (i = 0; i < 256; i++)
		next[i] = nSubLen;
	for (i = 0; i < nSubLen; i++)
		next[pDes[i]] = nSubLen - i;

	const unsigned char* naddr;
	for (naddr = pSrc; naddr <= pSrc + nLen - nSubLen; naddr += next[naddr[nSubLen]])
		if (memcmp(naddr, pDes, nSubLen) == 0)
			return naddr - pSrc + off;

	return -1;
}

