KrnlnApi int 取斐波那契数列项值(int n) {
	if (n == 0 || n == 1) {
		return n; // 第0项和第1项都是1
	}

	// 否则，第n项等于前两项之和
	return 取斐波那契数列项值(n - 1) + 取斐波那契数列项值(n - 2);
}