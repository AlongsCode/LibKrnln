#include <ctime>
#include <string>

#ifdef _WIN32
#include<windows.h>
KrnlnApi std::tm 取文件时间(const std::string& 文件名) {
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind = FindFirstFileA(文件名.c_str(), &FindFileData);
	std::tm Ret = { 0, 0, 0, 1, 1, 100 };
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if (FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &FindFileData.ftCreationTime))
		{
			SYSTEMTIME st;
			if (FileTimeToSystemTime(&FindFileData.ftCreationTime, &st)) {
				Ret = { st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };

			}
		}
	}
	return Ret;
}
KrnlnApi std::tm 取文件时间(const std::wstring& 文件名) {
	WIN32_FIND_DATAW FindFileData;
	HANDLE hFind = FindFirstFileW(文件名.c_str(), &FindFileData);
	std::tm Ret = { 0, 0, 0, 1, 1, 100 };
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		if (FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &FindFileData.ftCreationTime))
		{
			SYSTEMTIME st;
			if (FileTimeToSystemTime(&FindFileData.ftCreationTime, &st)) {
				Ret = { st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth - 1, st.wYear - 1900, st.wDayOfWeek, 0, 0 };

			}
		}
	}
	return Ret;
}
#else
//SYSTEMTIME转time_t

KrnlnApi std::tm 取文件时间(const std::string& filename) {
	struct _stat buf;

	//获得文件状态信息
	if (_stat(filename.c_str(), &buf) != 0) {
		return std::tm{ 0, 0, 0, 1, 1, 100 };
	}

	std::tm file_time{};
	gmtime_s(&file_time, &buf.st_mtime);
	return file_time;
}

std::tm KrnlnApi 取文件时间(const std::wstring& filename) {
	struct _stat buf;
	//获得文件状态信息
	if (_wstat(filename.c_str(), &buf) != 0) {
		return std::tm{ 0, 0, 0, 1, 1, 100 };
	}
	std::tm file_time{};
	gmtime_s(&file_time, &buf.st_mtime);
	return file_time;
}
#endif // _WIN32

