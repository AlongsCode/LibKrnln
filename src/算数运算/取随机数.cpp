#include <random>

KrnlnApi size_t 取随机数(size_t min, size_t max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dis(min, max);
	return dis(gen);
}