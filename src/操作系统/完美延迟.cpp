#include <Windows.h>
#include <thread>
#include <chrono>

KrnlnApi void ÍêÃÀÑÓ³Ù(long long milliseconds)
{
	HANDLE hThread = CreateThread(NULL, 0, [](LPVOID lpParam) -> DWORD {
		std::this_thread::sleep_for(std::chrono::milliseconds(*reinterpret_cast<long long*>(lpParam)));
		return 0;
	}, &milliseconds, 0, NULL);

	if (hThread != NULL)
	{
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
	}
}
