
KrnlnApi int 反转整数字节序(int 待反转的整数值)
{
	unsigned int nRes = 待反转的整数值 >> 24;
	nRes |= ((待反转的整数值 & 0x00FF0000) >> 8);
	nRes |= ((待反转的整数值 & 0x0000FF00) << 8);
	nRes |= ((待反转的整数值 & 0x000000FF) << 24);
	return nRes;
}


