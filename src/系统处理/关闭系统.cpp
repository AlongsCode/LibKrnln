#ifdef _WIN32
#pragma warning(disable:4996)
#include<windows.h>
// 调整当前进程的权限，使其具有关机、重启、注销系统的权限
static BOOL sSetPrivilege()
{
	OSVERSIONINFO osv = { 0 };
	osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osv);
	if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
			return FALSE;

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

		if (GetLastError() != ERROR_SUCCESS)
			return FALSE;
	}

	return TRUE;
}
KrnlnApi bool 关闭系统(int npMode, bool blpForceExit)
{
	if (npMode < 1 || npMode > 5 || sSetPrivilege() == FALSE)
		return FALSE;

	if (npMode >= 4)
		return SetSystemPowerState((npMode == 4), (BOOL)blpForceExit);

	UINT uFlags;
	if (npMode == 1)
	{
		OSVERSIONINFO osv = { 0 };
		osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osv);
		if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
			uFlags = EWX_POWEROFF;
		else
			uFlags = EWX_SHUTDOWN;
	}
	else
	{
		uFlags = (npMode == 2 ? EWX_REBOOT : EWX_LOGOFF);
	}

	if (blpForceExit)
		uFlags |= EWX_FORCE;

	return ExitWindowsEx(uFlags, 0);
}





#else

#include <stdlib.h>
#include <stdbool.h>

KrnlnApi bool 关闭系统(int action, bool force) {
	char command[64] = "";
	switch (action) {
	case 1:
		strcpy(command, "shutdown -h now");
		break;
	case 2:
		strcpy(command, "reboot");
		break;
	case 3:
		strcpy(command, "pkill -KILL -u $USER");
		break;
	case 4:
		strcpy(command, "systemctl suspend");
		break;
	case 5:
		strcpy(command, "systemctl hibernate");
		break;
	default:
		return false;
	}
	// 如果 force 为真，则将命令字符串末尾添加 "-f"
	if (force) {
		strcat(command, " -f");
	}
	return system(command) == 0;
}

#endif 




