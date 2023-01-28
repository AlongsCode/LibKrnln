#ifdef _WIN32
#include<windows.h>
KrnlnApi bool 是否为64位系统()
{
	SYSTEM_INFO sysInfo;
	GetNativeSystemInfo(&sysInfo);
	return  (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64);
}
#endif // _WIN32
