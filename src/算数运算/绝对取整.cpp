//#include"windows.h"
#include"math.h"
//算术运算 - 绝对取整

double  ProcessDouble(double num)
{
	double 小数部分;
	double result;
	double 整数部分;
	signed int addnum;

	小数部分 = modf(num, &整数部分);
	if (小数部分 < 0.0)
		小数部分 = -小数部分;
	if (小数部分 > 0.999999999999)//如果小数达到精度极限
	{
		addnum = -1;
		if (整数部分 >= 0.0) {
			addnum = 1;
		}
		result = (double)addnum + 整数部分;

	}
	else
	{
		result = num;
	}
	return result;
}

KrnlnApi int 绝对取整(double 数, double* 小数部分)
{
	double ret;
	double dnum;
	dnum = modf(ProcessDouble(数), &ret);
	if (小数部分)
	{
		*小数部分 = dnum;
	}

	return (int)ret;
}