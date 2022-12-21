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
typedef long LONG;
typedef unsigned short      WORD; typedef unsigned long       DWORD;
typedef ULONG_PTR DWORD_PTR, * PDWORD_PTR;
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))


/*
将第一个整数的低16位放置到结果整数的低16位，将第二个整数的低16位放置到结果整数的高16位，以此合并成一个整数，并返回合并后的结果
<int> 类型变量 <用作合并的整数2>

*/
KrnlnApi int 合并整数(int 低位, int 高位) {
	int n = MAKELONG(低位, 高位);
	return n;
}
