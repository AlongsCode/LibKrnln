#include"stdlib.h"
//#include"time.h"
//#include<optional>
//static time_t 随机数 = 0;
// void 置随机数种子(std::optional<unsigned int> 欲置入的种子数值)
//{
//	 if (欲置入的种子数值.has_value())
//	 {
//		 srand(欲置入的种子数值.value());
//	 }
//	 else
//	 {
//		 time_t _time = time(0);
//		 unsigned int seed = _time + 随机数;
//		 随机数 += _time + 随机数 + 100;
//		 srand(seed);
//	 }
//	
//}

KrnlnApi void 置随机数种子(unsigned int 欲置入的种子数值)
{
	srand(欲置入的种子数值);
}