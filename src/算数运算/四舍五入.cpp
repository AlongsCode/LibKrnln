#include"math.h"

inline double _round(double x)
{
	return floor(x + 0.5);
}


KrnlnApi double 四舍五入(double 欲被四舍五入的值, int 被舍入位置)
{
	if (被舍入位置 == 0)
		欲被四舍五入的值 = _round(欲被四舍五入的值);
	else if (被舍入位置 > 0)
	{
		double dbNum = pow((double)10.0, 被舍入位置);
		欲被四舍五入的值 = 欲被四舍五入的值 * dbNum;
		欲被四舍五入的值 = _round(欲被四舍五入的值) / dbNum;

	}
	else
	{
		被舍入位置 = abs(被舍入位置);
		double dbNum = pow((double)10.0, 被舍入位置);
		欲被四舍五入的值 = 欲被四舍五入的值 / dbNum;
		欲被四舍五入的值 = _round(欲被四舍五入的值) * dbNum;
	}
	return 欲被四舍五入的值;

}

