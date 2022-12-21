#include"windows.h"


//void 取长整数高低位(long long 预取长整数,int* 高位, int* 低位) {
//	LARGE_INTEGER* lNum = (LARGE_INTEGER*)&预取长整数;
//	*高位 = (int)lNum->HighPart;
//	*低位 = (int)lNum->LowPart;
//}

KrnlnApi void 取长整数高低位(long long A, int* a3, int* a4)
{
	int* pnum = (int*)&A;
	*a3 = pnum[1];
	*a4 = pnum[0];
}