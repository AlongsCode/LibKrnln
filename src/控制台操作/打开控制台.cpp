#include<windows.h>
#include<stdio.h>
KrnlnApi void 打开终端()
{
#ifdef _WIN32
	if (AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
	}
#else
	freopen("/dev/tty", "w", stdout);
#endif
}
