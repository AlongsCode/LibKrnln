#if defined(_WIN64)
typedef __int64 INT_PTR, * PINT_PTR;
typedef unsigned __int64 UINT_PTR, * PUINT_PTR;
typedef __int64 LONG_PTR, * PLONG_PTR;
typedef unsigned __int64 ULONG_PTR, * PULONG_PTR;
#define __int3264   __int64
#else
typedef int INT_PTR, * PINT_PTR;
typedef unsigned int UINT_PTR, * PUINT_PTR;
typedef long LONG_PTR, * PLONG_PTR;
typedef unsigned long ULONG_PTR, * PULONG_PTR;
#define __int3264   __int32
#endif

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef ULONG_PTR DWORD_PTR, * PDWORD_PTR;
#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))


/*
将第一个整数的低8位放置到结果短整数的低8位，将第二个整数的低8位放置到结果短整数的高8位，以此合并成一个短整数，并返回合并后的结果
<int> 类型变量 <用作合并的整数2>

*/

KrnlnApi short 合并短整数(int 低位, int 高位) {
	int n = MAKEWORD(低位, 高位);
	return n;
}


KrnlnApi short  合并短整数(char 低位, char 高位)
{
	char str[2] = { 低位, 高位 };
	char* 字符 = str;
	return *(short*)字符;
}