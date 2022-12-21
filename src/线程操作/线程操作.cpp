#ifdef _WIN32
#include<windows.h>
#pragma warning(disable:6258)
#pragma warning(disable:6001)
static bool bIsCSinit = false;
static LPCRITICAL_SECTION* s_CSList = NULL;
static CRITICAL_SECTION s_Cs;
static size_t count = 0, caption = 0;
inline void Enter()
{
	if (!bIsCSinit)
	{
		InitializeCriticalSection(&s_Cs);
		bIsCSinit = TRUE;
	}
	EnterCriticalSection(&s_Cs);
}
inline void Leave()
{
	if (bIsCSinit)
		LeaveCriticalSection(&s_Cs);
}
static bool check(LPCRITICAL_SECTION CS) {

	bool ret = false;
	for (size_t i = 0; i < count; i++)
	{
		if (s_CSList[i] == CS)//验证有效性
		{
			ret = true;
			break;
		}
	}
	return ret;
}
static bool add(LPCRITICAL_SECTION CS)
{
	Enter();
	bool ret = false;
	if (count >= caption)
	{
		// 数组已满，需要扩容，new更好一点，不会失败，只会抛异常，但是这个段选择纯c风格去写，编译环境大部分都是大于c++11的，推荐使用标准库
		LPCRITICAL_SECTION* new_list = (LPCRITICAL_SECTION*)realloc(s_CSList, (count + 1) * sizeof(LPCRITICAL_SECTION));
		if (new_list)
		{
			caption = (count + 1) * sizeof(LPCRITICAL_SECTION);
			s_CSList = new_list;//第一次的情况下
			s_CSList[count] = CS;
			count++;
			ret = true;
		}
		else {
			s_CSList = NULL;//内存块已损坏
			count = caption = 0;
		}
	}
	else
	{
		s_CSList[count] = CS;
		count++;
		ret = true;
	}

	Leave();
	return ret;
}
static void cleanup()
{
	Enter();

	if (bIsCSinit)
	{
		DeleteCriticalSection(&s_Cs);
		bIsCSinit = false;
	}

	if (s_CSList)
	{
		free(s_CSList);
		s_CSList = NULL;
		count = caption = 0;
	}

	Leave();
}
static bool myremove(LPCRITICAL_SECTION CS)
{
	Enter();
	bool ret = false;
	if (s_CSList)
	{

		for (size_t i = 0; i < count; i++)
		{
			if (s_CSList[i] == CS)//验证有效性
			{
				DeleteCriticalSection(s_CSList[i]);
				free(s_CSList[i]);//释放临界区资源
				for (size_t j = i; j < count - 1; j++)
				{
					s_CSList[j] = s_CSList[j + 1];
				}
				count--;
				ret = true;
				break;
			}
		}
		if (!count)//如果没有任何临界区资源时则清空
		{
			cleanup();
		}
	}
	Leave();
	return ret;
}

#elif __linux__
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
//未进行任何检查，如果需要傻瓜式操作的需要时间指针检查，防止传递垃圾指针
#else

#include <thread>
#include <mutex>
using SubPtr = void (*)(void*);

static std::mutex mt;
static std::vector <std::thread*> ThreadList;//用于验证互斥锁指针的合法性，vector本身是线程安全的，加号锁就可以
static std::mutex mm;
static std::vector <std::mutex*> MutexList;
static bool MyCreateThread(SubPtr function, void* data, std::thread** pRet)
{
	try
	{
		auto thread = new std::thread(function, data);
		thread->detach();
		if (pRet)
		{
			*pRet = thread;
		}
		return true;
	}
	catch (const std::system_error)
	{


		return false;
	}
}
inline void savepush(std::thread* t) {
	std::lock_guard<std::mutex> lock(mt);
	ThreadList.push_back(t);
}
inline void savepush(std::mutex* t) {
	std::lock_guard<std::mutex> lock(mm);
	MutexList.push_back(t);
}
inline bool saveremove(std::mutex* value)
{
	std::lock_guard<std::mutex> lock(mm);
	auto it = std::find(MutexList.begin(), MutexList.end(), value);
	if (it != MutexList.end())
	{
		delete* it;
		MutexList.erase(it);
		return true;
	}
	return false;
}
inline bool saveremove(std::thread* value)
{
	std::lock_guard<std::mutex> lock(mt);
	auto it = std::find(ThreadList.begin(), ThreadList.end(), value);
	if (it != ThreadList.end())
	{
		delete* it;
		ThreadList.erase(it);
		return true;
	}
	return false;
}

inline bool check(std::mutex* t) {
	return std::find(MutexList.begin(), MutexList.end(), t) != MutexList.end();
}
inline bool check(std::thread* t) {
	return std::find(ThreadList.begin(), ThreadList.end(), t) != ThreadList.end();
}
inline bool wait_thread(std::thread* t, int time) {
	std::atomic<bool> done{ false };
	std::thread timer{ [&] {
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		done.store(true);
	} };

	t->join();
	timer.join();
	return !done.load();
}

inline void savepush(std::thread* t) {
	std::lock_guard<std::mutex> lock(mt);
	ThreadList.push_back(t);
}

#endif 
KrnlnApi void* 启动线程(void(*callback)(void*), void* arg) {

#ifdef _WIN32
	return  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)callback, arg, 0, 0);
#elif __linux__
	pthread_t result;
	pthread_t newthread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&newthread, &attr, (void* (*)(void*))callback, arg);
	pthread_attr_destroy(&attr);
	return  newthread;
#else

	std::thread* hThread = nullptr;
	if (MyCreateThread(callback, arg, &hThread)) {
		savepush(hThread);

	}
	return hThread;
#endif 
};


//调用格式: SDT_INT 创建进入许可证, 命令说明 : "创建并返回一个进入许可证数值，此许可证值用作进入程序中的指定许可代码区，以避免多线程冲突。成功返回非零整数值，失败返回0。所创建的许可证在不再使用后，必须使用“删除进入许可证”命令将其删除"
//无参数
KrnlnApi void* 创建进入许可证()
{
#if _WIN32
	LPCRITICAL_SECTION cs = (LPCRITICAL_SECTION)malloc(sizeof(RTL_CRITICAL_SECTION));
	if (cs)
	{
		InitializeCriticalSection(cs);
		if (add(cs)) {
			return cs;
		}
		else
		{
			free(cs);

		}
	}
	return nullptr;

#elif __linux__
	pthread_mutex_t* mutex;
	mutex = new pthread_mutex_t;
	pthread_mutex_init(mutex, 0);
	memset(mutex, 0, sizeof(pthread_mutex_t));
	return mutex;
#else
	std::mutex* temp = new std::mutex;
	savepush(temp);
	return temp;
#endif
}


KrnlnApi bool 删除进入许可证(void* pmutex)
{
#if _WIN32
	return myremove((LPCRITICAL_SECTION)pmutex);
#elif __linux__
	pthread_mutex_t* mutex = (pthread_mutex_t*)pmutex;
	pthread_mutex_destroy(mutex);
	delete mutex;
	return true;
#else
	pRetData->m_bool = saveremove((std::mutex*)pArgInf[0].m_int);
#endif
}

KrnlnApi void 进入许可区(void* pmutex)
{
#if _WIN32
	if (check((LPCRITICAL_SECTION)pmutex))
	{
		EnterCriticalSection((LPCRITICAL_SECTION)pmutex);
	}
#elif __linux__
	pthread_mutex_lock((pthread_mutex_t*)pmutex)
#else
	std::mutex* m = (std::mutex*)pmutex;
	if (check(m))
	{
		try
		{
			// 尝试加锁
			m->lock();
		}
		catch (const std::system_error)
		{
			// 如果加锁失败，说明线程中存在此互斥量
			return;

		}
	}
#endif
}

KrnlnApi void 退出许可区(void* pmutex)
{
#if _WIN32
	if (check((LPCRITICAL_SECTION)pmutex))
	{
		LeaveCriticalSection((LPCRITICAL_SECTION)pmutex);
	}
#elif __linux__
	pthread_mutex_unlock((pthread_mutex_t*)pmutex)
#else
	std::mutex* m = (std::mutex*)pmutex;
	if (check(m))
	{
		m->try_lock();//尝试加锁，失败与否都一定有锁，防止解锁抛出异常
		m->unlock();

	}
#endif

}

KrnlnApi bool 等待线程(void* pThread, int time)
{
#if _WIN32

	return  WaitForSingleObject((HANDLE)pThread, time) != -1;
#elif __linux__
	pthread_join((pthread_t)pThread, 0) == 0;
#else
	std::thread* arg1 = (std::thread*)pThread;
	if (check(arg1))
	{
		if (time)
		{
			return wait_thread(arg1, time);
		}
		else
		{
			arg1->join();//直接尝试加入
			return  true;
		}
	}
	return  false;
#endif
}


// 调用格式: SDT_BOOL 强制结束线程, 命令说明: "返回真表示执行成功。"
// 参数<1>: 线程句柄 SDT_INT, 参数说明: "可通过“启动线程”的第三个参数获取线程句柄。"
KrnlnApi bool 强制结束线程(void* pThread)
{
#if _WIN32
	DWORD ExitCode;
	GetExitCodeThread((HANDLE)pThread, &ExitCode);
	return TerminateThread((HANDLE)pThread, ExitCode);
#elif __linux__
	return pthread_cancel((pthread_t)pThread) == 0;
#else
	return  saveremove((std::thread*)pThread);
#endif
}


KrnlnApi bool 关闭线程句柄(void* pThread)
{

#if _WIN32
	return  CloseHandle((HANDLE)pThread) != 0;
#elif __linux__
	return pthread_detach((pthread_t)pThread) == 0;
#else
	return true;//标准库不做任何处理
#endif
}

