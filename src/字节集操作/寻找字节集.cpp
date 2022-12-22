#include<vector>
using namespace std;
//我的代码，速度不如7号
//#include <unordered_map>
//intptr_t reverse_find_bytes(const std::vector<unsigned char>& src, const std::vector<unsigned char>& sub) {
//	if (sub.empty() || src.empty()) return -1;
//	const intptr_t src_len = src.size();
//	const intptr_t sub_len = sub.size();
//	if (sub_len > src_len) return -1;
//	const unsigned char* p_src = src.data();
//	const unsigned char* p_sub = sub.data();
//
//	std::unordered_map<unsigned char, intptr_t> skip_table;
//	for (intptr_t i = 0; i < sub_len - 1; ++i) {
//		skip_table[p_sub[i]] = sub_len - i - 1;
//	}
//
//	intptr_t i = sub_len - 1;
//	intptr_t j;
//	while (i < src_len) {
//		for (j = sub_len - 1; p_src[i] == p_sub[j]; --i, --j) {
//			if (j == 0) {
//				return i;
//			}
//		}
//		i += skip_table.find(p_src[i]) != skip_table.end() ? skip_table[p_src[i]] : sub_len;
//	}
//	return -1;
//}

// 改自被封七号
KrnlnApi size_t 寻找字节集(const vector<unsigned char>& s, const vector<unsigned char>& p, size_t boff) {
	if (s.empty() || p.empty())
		return -1;

	size_t nLen = s.size();
	size_t nSubLen = p.size();

	const unsigned char* pSrc;
	size_t off;
	if (boff <= 1)
	{
		off = 1;
		pSrc = s.data();
	}
	else
	{
		off = boff;
		pSrc = s.data() + off - 1;
		nLen -= off - 1;
	}

	if (nLen <= 0 || nSubLen <= 0 || nSubLen > nLen)
		return -1;

	const  unsigned char* pDes = p.data();
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



KrnlnApi size_t 寻找字节集下标(const vector<unsigned char>& 被搜寻的字节集, const vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置) {
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
			return i + off - 1;
		else
			return -1;
	case 2:
		for (i = 0; i < nLen - 1; i++)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				return i + off - 1;
		return -1;
	case 3:
		for (i = 0; i < nLen - 2; i++)
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0])
				if (pSrc[i + 2] == pDes[2])
					return i + off - 1;
		return -1;
	case 4:
		for (i = 0; i < nLen - 3; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				return i + off - 1;
		return -1;
	case 5:
		for (i = 0; i < nLen - 4; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (pSrc[i + 4] == pDes[4])
					return i + off - 1;
		return -1;
	case 6:
		for (i = 0; i < nLen - 5; i++)
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0])
				if (((short*)(pSrc + i + 4))[0] == ((short*)(pDes + 4))[0])
					return i + off - 1;
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
			return naddr - pSrc + off - 1;

	return -1;
}