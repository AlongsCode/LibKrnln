//取整数型某一位的值，为1返回真，为0返回假 位号为0-31
KrnlnApi bool 取整数型某位(int 整数, char 位号)
{
	return (整数 & (unsigned int)(1 << 位号)) >> 位号;
}