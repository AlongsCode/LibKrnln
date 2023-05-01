#include<string>
#include<optional>
#include<vector>
#include <limits>

#include<windows.h>

enum class 打开方式
{
	读入 = 1,//从指定文件读入数据，如果该文件不存在则失败；
	写出,//写出数据到指定文件，如果该文件不存在则失败；
	读写,//从文件中读入数据或者写出数据到文件，如果该文件不存在则失败；
	重写,//写出数据到指定文件。如果该文件不存在则先创建一个新文件，如果已经存在就先清除其中的所有数据；
	改写,//写出数据到指定文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开；
	改读//从文件中读入数据或者写出数据到文件。如果该文件不存在则创建一个新文件，如果已经存在就直接打开。
};
enum class 共享方式
{
	无限制 = 1,//：允许其它进程任意读写此文件；
	禁止读,//：禁止其它进程读此文件；
	禁止写,//：禁止其它进程写此文件；
	禁止读写,//：禁止其它进程读写此文件。
};
enum class 文件读写位置
{
	文件首 = 1,
	文件尾,
	现行位置
};
class KrnlnApi 文件
{
public:
	文件(const std::string& 欲打开的文件名称,
		打开方式 文件打开方式 = 打开方式::读写,
		共享方式 文件共享方式 = 共享方式::无限制);
	文件(const std::wstring& 欲打开的文件名称,
		打开方式 文件打开方式,
		共享方式 文件共享方式);

	~文件();

private:
	HANDLE hFile;
public:
	bool 是否已打开() const {
		return hFile != NULL && hFile != INVALID_HANDLE_VALUE;
	}
	bool 打开(const std::string& 欲打开的文件名称,
		打开方式 文件打开方式 = 打开方式::读写,
		共享方式 文件共享方式 = 共享方式::无限制
	);
	bool 打开(const std::wstring& 欲打开的文件名称,
		打开方式 文件打开方式 = 打开方式::读写,
		共享方式 文件共享方式 = 共享方式::无限制
	);
	bool 锁住文件(std::uint64_t 欲加锁或解锁的位置, std::uint64_t 欲加锁或解锁的长度, std::optional<std::uint64_t> 加锁重试时间 = std::nullopt);
	bool 解锁文件(std::uint64_t 欲加锁或解锁的位置, std::uint64_t 欲加锁或解锁的长度);
	bool 写出字节集(const std::vector<unsigned char>& 数据);
	bool 写出字节集(unsigned char* 数据, size_t 长度);
	bool 关闭();
	bool 移动读写位置(文件读写位置 起始移动位置, std::int64_t 移动距离);
	bool 移到文件首();
	bool 移到文件尾();
};


bool 文件::打开(const std::string& 欲打开的文件名称, 打开方式 文件打开方式, 共享方式 文件共享方式)
{
	//如果文件已经打开,直接返回假
	if (是否已打开())
		return false;

	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
	switch (文件打开方式)
	{
	case 打开方式::读入:
		dwDesiredAccess = GENERIC_READ;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::写出:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::重写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = CREATE_ALWAYS;
		break;
	case 打开方式::改写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	case 打开方式::改读:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	default:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	}


	if (文件共享方式 == 共享方式::禁止读)
		dwShareMode = FILE_SHARE_WRITE;
	else if (文件共享方式 == 共享方式::禁止写)
		dwShareMode = FILE_SHARE_READ;
	else if (文件共享方式 == 共享方式::禁止读写)
		dwShareMode = 0;
	else
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);


	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	hFile = CreateFileA(欲打开的文件名称.c_str(),
		dwDesiredAccess,
		dwShareMode,
		&sa,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	return true;
}
bool 文件::打开(const std::wstring& 欲打开的文件名称, 打开方式 文件打开方式, 共享方式 文件共享方式)
{
	//如果文件已经打开,直接返回假
	if (是否已打开())
		return false;

	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
	switch (文件打开方式)
	{
	case 打开方式::读入:
		dwDesiredAccess = GENERIC_READ;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::写出:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::重写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = CREATE_ALWAYS;
		break;
	case 打开方式::改写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	case 打开方式::改读:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	default:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	}


	if (文件共享方式 == 共享方式::禁止读)
		dwShareMode = FILE_SHARE_WRITE;
	else if (文件共享方式 == 共享方式::禁止写)
		dwShareMode = FILE_SHARE_READ;
	else if (文件共享方式 == 共享方式::禁止读写)
		dwShareMode = 0;
	else
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);


	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	hFile = CreateFileW(欲打开的文件名称.c_str(),
		dwDesiredAccess,
		dwShareMode,
		&sa,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;
	return true;
}
bool 文件::锁住文件(std::uint64_t 欲加锁或解锁的位置, std::uint64_t 欲加锁或解锁的长度, std::optional<std::uint64_t> 加锁重试时间)
{
	if (!是否已打开())
	{
		return false;
	}

	OVERLAPPED overlapped{ 0 };
	overlapped.Offset = static_cast<DWORD>(欲加锁或解锁的位置);
	overlapped.OffsetHigh = static_cast<DWORD>(欲加锁或解锁的位置 >> 32);

	DWORD flags = LOCKFILE_FAIL_IMMEDIATELY;
	if (加锁重试时间.has_value())
	{
		if (加锁重试时间.value() == -1)
		{
			flags = 0;
		}
		else if (加锁重试时间.value() > 0)
		{
			const auto beginTickCount = GetTickCount64();
			while (true)
			{
				if (::LockFileEx(hFile, flags, 0, static_cast<DWORD>(欲加锁或解锁的长度), static_cast<DWORD>(欲加锁或解锁的长度 >> 32), &overlapped))
				{
					return true;
				}
				const DWORD lastError = ::GetLastError();
				if ((lastError != ERROR_SHARING_VIOLATION && lastError != ERROR_LOCK_VIOLATION) ||
					GetTickCount64() - beginTickCount > 加锁重试时间.value())
				{
					break;
				}
			}
			return false;
		}
	}

	return ::LockFileEx(hFile, flags, 0, static_cast<DWORD>(欲加锁或解锁的长度), static_cast<DWORD>(欲加锁或解锁的长度 >> 32), &overlapped);
}

bool 文件::解锁文件(std::uint64_t 欲加锁或解锁的位置, std::uint64_t 欲加锁或解锁的长度) {

	LARGE_INTEGER liPos;
	liPos.QuadPart = 欲加锁或解锁的位置;
	LARGE_INTEGER liLength;
	liLength.QuadPart = 欲加锁或解锁的长度;
	return UnlockFile(hFile, liPos.LowPart, liPos.HighPart, liLength.LowPart, liLength.HighPart);


}

bool 文件::写出字节集(const std::vector<unsigned char>& 数据)
{
#undef min
#undef  max
	if (!是否已打开())
	{
		return false;
	}

	size_t 写入总数 = 0;
	const auto 数据大小 = 数据.size();
	size_t 分段大小 = std::numeric_limits<DWORD>::max();
	while (写入总数 < 数据大小)
	{
		const auto 剩余大小 = 数据大小 - 写入总数;
		const auto 本次写入大小 = std::min(分段大小, 剩余大小);

		DWORD dwNumOfByteWritten;
		if (!WriteFile(hFile, 数据.data() + 写入总数, static_cast<DWORD>(本次写入大小), &dwNumOfByteWritten, nullptr))
		{
			return false;
		}

		写入总数 += 本次写入大小;
	}
	return true;
}
bool 文件::写出字节集(unsigned char* 数据, size_t 长度) {
#undef min
#undef  max
	if (!是否已打开())
	{
		return false;
	}

	size_t 写入总数 = 0;
	const auto 数据大小 = 长度;
	size_t 分段大小 = std::numeric_limits<DWORD>::max();
	while (写入总数 < 数据大小)
	{
		const auto 剩余大小 = 数据大小 - 写入总数;
		const auto 本次写入大小 = std::min(分段大小, 剩余大小);

		DWORD dwNumOfByteWritten;
		if (!WriteFile(hFile, 数据 + 写入总数, static_cast<DWORD>(本次写入大小), &dwNumOfByteWritten, nullptr))
		{
			return false;
		}

		写入总数 += 本次写入大小;
	}
	return true;
}

bool 文件::关闭()
{

	if (CloseHandle(hFile)) {
		hFile = NULL;
		return true;
	};
	return false;
}

bool 文件::移动读写位置(文件读写位置 起始移动位置, std::int64_t 移动距离)
{
	LARGE_INTEGER liDistanceToMove;
	liDistanceToMove.QuadPart = 移动距离;

	LARGE_INTEGER liNewFilePointer;

	DWORD dwMoveMethod;
	switch (起始移动位置)
	{
	case 文件读写位置::文件尾:
		dwMoveMethod = FILE_END;
		break;
	case 文件读写位置::现行位置:
		dwMoveMethod = FILE_CURRENT;
		break;
	default:
		dwMoveMethod = FILE_BEGIN;
		break;
	}


	return SetFilePointerEx(hFile, liDistanceToMove, &liNewFilePointer, dwMoveMethod) == TRUE;

}

bool 文件::移到文件首() {

	return SetFilePointer(hFile, 0, NULL, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
}
bool 文件::移到文件尾() {
	return SetFilePointer(hFile, 0, NULL, FILE_END) != INVALID_SET_FILE_POINTER;;

}


文件::文件(const std::wstring& 欲打开的文件名称,
	打开方式 文件打开方式,
	共享方式 文件共享方式) :hFile(NULL) {
	//如果文件已经打开,直接返回假
	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
	switch (文件打开方式)
	{
	case 打开方式::读入:
		dwDesiredAccess = GENERIC_READ;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::写出:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::重写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = CREATE_ALWAYS;
		break;
	case 打开方式::改写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	case 打开方式::改读:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	default:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	}


	if (文件共享方式 == 共享方式::禁止读)
		dwShareMode = FILE_SHARE_WRITE;
	else if (文件共享方式 == 共享方式::禁止写)
		dwShareMode = FILE_SHARE_READ;
	else if (文件共享方式 == 共享方式::禁止读写)
		dwShareMode = 0;
	else
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	hFile = CreateFileW(欲打开的文件名称.c_str(),
		dwDesiredAccess,
		dwShareMode,
		&sa,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
}
文件::~文件()
{
	关闭();
}
;
文件::文件(const std::string& 欲打开的文件名称,
	打开方式 文件打开方式,
	共享方式 文件共享方式) :hFile(NULL) {
	//如果文件已经打开,直接返回假
	DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
	switch (文件打开方式)
	{
	case 打开方式::读入:
		dwDesiredAccess = GENERIC_READ;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::写出:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	case 打开方式::重写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = CREATE_ALWAYS;
		break;
	case 打开方式::改写:
		dwDesiredAccess = GENERIC_WRITE;
		dwCreationDisposition = OPEN_ALWAYS;
		break;
	case 打开方式::改读:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	default:
		dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		dwCreationDisposition = OPEN_EXISTING;
		break;
	}


	if (文件共享方式 == 共享方式::禁止读)
		dwShareMode = FILE_SHARE_WRITE;
	else if (文件共享方式 == 共享方式::禁止写)
		dwShareMode = FILE_SHARE_READ;
	else if (文件共享方式 == 共享方式::禁止读写)
		dwShareMode = 0;
	else
		dwShareMode = (FILE_SHARE_READ | FILE_SHARE_WRITE);


	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	hFile = CreateFileA(欲打开的文件名称.c_str(),
		dwDesiredAccess,
		dwShareMode,
		&sa,
		dwCreationDisposition,
		FILE_ATTRIBUTE_ARCHIVE,
		0);
}