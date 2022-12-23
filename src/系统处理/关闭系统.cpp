#ifdef _WIN32
#pragma warning(disable:4996)
#include<windows.h>
// 调整当前进程的权限，使其具有关机、重启、注销系统的权限
static void adjustPrivileges() {
	// 获取当前进程的令牌
	HANDLE hToken;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	// 获取关机、重启、注销系统的特权标识
	LUID Luid;
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &Luid);

	// 设置当前进程的权限
	TOKEN_PRIVILEGES NewPermission, OldNewPermission;
	NewPermission.PrivilegeCount = 1;
	NewPermission.Privileges->Luid = Luid;
	NewPermission.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &NewPermission, sizeof(TOKEN_PRIVILEGES), &OldNewPermission, NULL);
}
KrnlnApi bool 关闭系统(int action, bool force)
{
	bool result = false;
	UINT uFlag = 0;
	adjustPrivileges();
	if (action >= 1 && action <= 5)
	{
		if (action < 4)
		{
			if (action == 1)
			{
				OSVERSIONINFO osv = { 0 };
				osv.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
				GetVersionEx(&osv);
				if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT)
					uFlag = EWX_POWEROFF;
				else
					uFlag = EWX_SHUTDOWN;
			}
			else if (action == 2)
			{

				uFlag = EWX_REBOOT;
			}
			else
			{
				uFlag = EWX_LOGOFF;
			}
			if (force)
				uFlag = uFlag | EWX_FORCE;
			// 执行关机、重启、注销操作
			result = ExitWindowsEx(uFlag, 0);

		}
		else
		{	// 休眠或唤醒
			result = SetSystemPowerState(action == 4, force);

		}
	}
	return result;
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




