#include <cmath>

class NumericIntegration
{
private:
	double IntegrateBySimpson13(int sampleInterval, double lowerLimit, double upperLimit) {
		// Simpson 1/3 法计算积分

		// 计算区间长度
		double intervalLength = upperLimit - lowerLimit;

		// 计算步长
		double step = intervalLength / sampleInterval;

		double integral = 0.0;

		// 计算所有子区间的积分值并求和
		for (int i = 0; i < sampleInterval; i++)
		{
			double x0 = lowerLimit + i * step;
			double x1 = x0 + step;
			integral += (Function(x0) + 4 * Function((x0 + x1) / 2) + Function(x1)) * step / 6;
		}

		return integral;
	};
	double IntegrateBySimpson38(int sampleInterval, double lowerLimit, double upperLimit)
	{
		// Simpson 3/8 法计算积分

		// 计算区间长度
		double intervalLength = upperLimit - lowerLimit;

		// 计算步长
		double step = intervalLength / sampleInterval;

		double integral = 0.0;

		// 计算所有子区间的积分值并求和
		for (int i = 0; i < sampleInterval; i++)
		{
			double x0 = lowerLimit + i * step;
			double x1 = x0 + step;
			integral += (Function(x0) + 3 * Function(x0 + step / 3) + 3 * Function(x0 + 2 * step / 3) + Function(x1)) * step / 8;
		}

		return integral;
	};
	double(*Function)(double);
public:
	double Integrate(double(*F)(double), int sampleInterval, double lowerLimit, double upperLimit)
	{
		if (!F)
		{
			return 0;
		}
		Function = F;
		// 使用 Simpson 1/3 法和 Simpson 3/8 法计算积分
		return IntegrateBySimpson13(sampleInterval, lowerLimit, upperLimit) + IntegrateBySimpson38(sampleInterval, lowerLimit, upperLimit);
	}
};


KrnlnApi int 数值积分计算(double(*函数)(double), int 样本区间, double 积分下限, double 积分上限)
{
	NumericIntegration IntegrateVector;
	// 调用 Integrate 函数计算积分
	return IntegrateVector.Integrate(函数, 样本区间, 积分下限, 积分上限);
}






