﻿
//算术运算 - 取符号
/*
	调用格式： 〈整数型〉 取符号 （双精度小数型 欲取其符号的数值） - 系统核心支持库->算术运算
	英文名称：sgn
	返回一个整数，如果小于零，表明给定数值为负；如果等于零，表明给定数值为零；如果大于零，表明给定数值为正。本命令为初级命令。
	参数<1>的名称为“欲取其符号的数值”，类型为“双精度小数型（double）”。
*/
KrnlnApi int 取符号(double 数) {
	int n = 0;
	if (数 > 0)
		n = 1;
	else if (数 < 0)
		n = -1;
	return n;
}
