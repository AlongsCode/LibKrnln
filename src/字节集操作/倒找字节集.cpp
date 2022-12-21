#include"vector"



KrnlnApi intptr_t 倒找字节集(const std::vector<unsigned char>& 被搜寻的字节集, const std::vector<unsigned char>& 欲寻找的字节集, size_t 起始搜寻位置) {

	if (欲寻找的字节集.size() == 0 || 欲寻找的字节集.empty() || 被搜寻的字节集.empty()) {
		return -1;
	}
	size_t nLen = 被搜寻的字节集.size();
	size_t nSubLen = 欲寻找的字节集.size();
	if (nLen == 0 || nSubLen == 0 || nSubLen > nLen) return -1;
	// 计算起始搜寻位置
	size_t off = 起始搜寻位置;
	if (off < 1) return -1;
	if (off <= nLen) nLen = off;
	if (nLen < nSubLen) return -1;
	off = nLen - nSubLen;
	const unsigned char* pSrc = 被搜寻的字节集.data();
	const unsigned char* pDes = 欲寻找的字节集.data();

	// 短子串直接暴力搜索
	if (nSubLen == 1)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--)
		{
			if (pSrc[i] == pDes[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 2)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 3)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0]) {
				if (pSrc[i + 2] == pDes[2]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	else if (nSubLen == 4)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 5)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				if (pSrc[i + 4] == pDes[4]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	else if (nSubLen == 6)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				if (((short*)(pSrc + i + 4))[0] == ((short*)(pDes + 4))[0]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	size_t next[256];
	for (size_t i = 0; i < 256; i++) {
		next[i] = nSubLen;
	}
	for (size_t i = nSubLen; i > 0; i--) {
		next[pDes[i - 1]] = i;
	}

	// 从起始位置开始倒序搜索
	const unsigned char* naddr = pSrc + off;
	for (; naddr >= pSrc; naddr -= next[naddr[-1]]) {
		if (memcmp(naddr, pDes, nSubLen) == 0) {
			return naddr - pSrc + 1;
		}
	}

	return -1;
}
KrnlnApi intptr_t 倒找字节集(const std::vector<unsigned char>& 被搜寻的字节集, const std::vector<unsigned char>& 欲寻找的字节集) {

	if (欲寻找的字节集.empty() || 被搜寻的字节集.empty()) return -1;
	// 计算需要搜索的字节集的长度和被搜索的字节集的长度
	size_t src_len = 被搜寻的字节集.size();
	size_t nSubLen = 欲寻找的字节集.size();
	// 如果需要搜索的字节集长度为 0 或者被搜索的字节集长度小于需要搜索的字节集长度，则返回 -1
	if (nSubLen == 0 || nSubLen > src_len) return -1;
	// 获取被搜索的字节集的数据
	const unsigned char* pSrc = 被搜寻的字节集.data();
	// 如果被搜索的字节集长度小于需要搜索的字节集长度，则返回 -1
	if (src_len < nSubLen) return -1;
	// 计算偏移量
	size_t off = src_len - nSubLen;
	// 获取需要搜索的字节集的数据
	const unsigned char* pDes = 欲寻找的字节集.data();
	// 短子串直接暴力搜索
	if (nSubLen == 1)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--)
		{
			if (pSrc[i] == pDes[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 2)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 3)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((short*)(pSrc + i))[0] == ((short*)pDes)[0]) {
				if (pSrc[i + 2] == pDes[2]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	else if (nSubLen == 4)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				return i + 1;
			}
		}
		return -1;
	}
	else if (nSubLen == 5)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				if (pSrc[i + 4] == pDes[4]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	else if (nSubLen == 6)
	{
		size_t i = off;
		for (size_t p = 0; p < off; p++, i--) {
			if (((int*)(pSrc + i))[0] == ((int*)pDes)[0]) {
				if (((short*)(pSrc + i + 4))[0] == ((short*)(pDes + 4))[0]) {
					return i + 1;
				}
			}
		}
		return -1;
	}
	// 初始化 next 数组
	size_t next[256];
	for (size_t i = 0; i < 256; i++) {
		next[i] = nSubLen;
	}
	// 根据需要搜索的字节集来更新 next 数组
	for (size_t i = nSubLen; i > 0; i--) {
		next[pDes[i - 1]] = i;
	}
	// 计算需要搜索的字节集的首地址
	const unsigned char* addr = pSrc + off;
	// 循环搜索
	for (; addr >= pSrc; addr -= next[addr[-1]]) {
		// 如果找到了需要搜索的字节集，则返回其在被搜索的字节集中的位置
		if (memcmp(addr, pDes, nSubLen) == 0) {
			return addr - pSrc + 1;
		}
	}
	return -1;
}

