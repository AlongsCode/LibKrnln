#include<cmath>
double __cdecl ProcessDouble1(double a1)
{
	double v1; // st7@1
	double result; // st7@6
	double v3; // [sp+0h] [bp-8h]@1
	signed int v4; // [sp+Ch] [bp+4h]@4

	v1 = modf(a1, &v3);
	if (v1 < 0.0)
		v1 = -v1;
	if (v1 <= 0.999999999999)
	{
		result = a1;
	}
	else
	{
		v4 = -1;
		if (v3 >= 0.0)
			v4 = 1;
		result = (double)v4 + v3;
	}
	return result;
}

KrnlnApi int 取整(double 数)
{
	return (int)floor(ProcessDouble1(数));
}