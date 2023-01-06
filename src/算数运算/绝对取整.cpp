#include<cmath>
//算术运算 - 绝对取整


KrnlnApi int 绝对取整(double x) {
	return x < 0.0 ? std::ceil(x) : std::floor(x);
}