KrnlnApi bool 是否素数(unsigned long long x)
{
	if (x < 2) {
		// 小于 2 的数都不是素数
		return false;
	}
	if (x == 2 || x == 3) {
		// 2 和 3 是素数
		return true;
	}
	if (x % 2 == 0 || x % 3 == 0) {
		// 如果能够被 2 或 3 整除，则不是素数
		return false;
	}
	// 从 5 开始枚举到 sqrt(x)，如果 x 能够被枚举到的数整除，则不是素数
	for (unsigned long long i = 5; i * i <= x; i += 6) {
		if (x % i == 0 || x % (i + 2) == 0) {
			return false;
		}
	}
	// 如果没有被整除，则是素数
	return true;
}