#include <cmath>

class NumericIntegration
{
private:
	double IntegrateBySimpson13(int sampleInterval, double lowerLimit, double upperLimit) {
		// Simpson 1/3 ���������

		// �������䳤��
		double intervalLength = upperLimit - lowerLimit;

		// ���㲽��
		double step = intervalLength / sampleInterval;

		double integral = 0.0;

		// ��������������Ļ���ֵ�����
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
		// Simpson 3/8 ���������

		// �������䳤��
		double intervalLength = upperLimit - lowerLimit;

		// ���㲽��
		double step = intervalLength / sampleInterval;

		double integral = 0.0;

		// ��������������Ļ���ֵ�����
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
		// ʹ�� Simpson 1/3 ���� Simpson 3/8 ���������
		return IntegrateBySimpson13(sampleInterval, lowerLimit, upperLimit) + IntegrateBySimpson38(sampleInterval, lowerLimit, upperLimit);
	}
};


KrnlnApi int ��ֵ���ּ���(double(*����)(double), int ��������, double ��������, double ��������)
{
	NumericIntegration IntegrateVector;
	// ���� Integrate �����������
	return IntegrateVector.Integrate(����, ��������, ��������, ��������);
}






