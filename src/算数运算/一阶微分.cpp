#include<cmath>


/*��� Runge-Kutta ��*/
class DifferentialEquationSolver {
private:
	double x_known, y_known;
	double error_tolerance;
	double initial_step_size, min_step_size;
	double(*f)(double, double);
public:
	DifferentialEquationSolver(double(*fun)(double, double), double x_known, double y_known, double error_tolerance, double initial_step_size, double min_step_size) :
		f(fun), x_known(x_known), y_known(y_known), error_tolerance(error_tolerance), initial_step_size(initial_step_size), min_step_size(min_step_size) {}
	bool solve(double x, double& y_estimate) {
		double step_size = initial_step_size;
		while (true) {
			double k1 = step_size * f(x_known, y_known);
			double k2 = step_size * f(x_known + step_size / 2, y_known + k1 / 2);
			double k3 = step_size * f(x_known + step_size / 2, y_known + k2 / 2);
			double k4 = step_size * f(x_known + step_size, y_known + k3);
			double error_estimate = fabs(k1 / 6 - k2 / 3 + k3 / 3 - k4 / 6);
			if (error_estimate < error_tolerance * step_size / 32) {
				step_size *= 2;
			}
			else if (error_estimate > error_tolerance * step_size) {
				step_size /= 2;
			}
			if (step_size < min_step_size) {
				return false;
			}
			x_known += step_size;
			y_known += (k1 + k2 + k3 + k4) / 6;
			if (x_known >= x) {
				y_estimate = y_known;
				return true;
			}
		}
	}
};

KrnlnApi bool һ��΢��(double(*һ��΢�ַ���)(double, double), double ��֪��xֵ, double ��֪��yֵ, double Ҫ����xֵ, double ��������, double ��ʼ����, double ��С����) {
	DifferentialEquationSolver solver(һ��΢�ַ���, ��֪��xֵ, ��֪��yֵ, ��������, ��ʼ����, ��С����);
	double y;
	return  solver.solve(Ҫ����xֵ, y);
}