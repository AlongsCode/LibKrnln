#include<windows.h>
#include<wininet.h>
#pragma comment(lib,"Wininet.lib")
KrnlnApi bool 是否联网() {

	DWORD flag;
	return InternetGetConnectedState(&flag, 0);;

}