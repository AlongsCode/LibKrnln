#include<string>
#ifdef _WIN32
#include<windows.h>
#pragma comment(lib,"Ws2_32.lib")
#else
#include<unistd.h>
#endif



KrnlnApi std::string 取本机名()
{
	char name[260] = { 0 };
	if (gethostname(name, 260) == 0)
	{
		return std::string(name);
	}
	else
	{
		return std::string();
	}
}