#ifdef _WIN32
#pragma warning(disable:6258)
#include"windows.h"
#include"vector"
#include"string"
#include"midi.hpp"
using namespace std;
namespace KrnlnMidInside {
	struct MIDIFILEDATAINFO
	{
		unsigned char* pData;
		size_t	dwSize;
	};
	struct MIDMUSIC
	{
		union {
			const char* name;
			const wchar_t* wname;
			MIDIFILEDATAINFO data;
		};
		int datatype;
	};
	typedef MIDMUSIC* PMIDMUSIC;
	MIDIFILEDATAINFO* pMidiFileData = NULL;
	static int nLoopNum;
	static int nPlayWaitTime;
	static size_t nMidiArrySize = 0;
	static HANDLE	hLoopPlayEvent = NULL;
	static HANDLE  hMidiPlayerThrd = NULL;
	static CMIDI* pMidiPlayer = NULL;
	typedef void (*PDESTROY)(void);
	static PDESTROY DestroyMidiPlayer;
	BOOL IsValidMidiDataPtr(MIDIFILEDATAINFO pData)
	{
		if (pData.pData == NULL) {
			return FALSE;
		}
		if (pData.dwSize > (3 * sizeof(WORD) + 2 * sizeof(DWORD))) {
			return TRUE;
		}
		return FALSE;

	}
	BOOL IsValidMidiFileName(LPCSTR pStr)
	{
		if (pStr == NULL)return FALSE;
		size_t nLen = strlen(pStr);
		if (nLen >= 4)
			return TRUE;
		return FALSE;
	}
	BOOL IsValidMidiFileName(LPCWSTR pStr)
	{
		if (pStr == NULL)return FALSE;
		size_t nLen = wcslen(pStr);
		if (nLen >= 4)
			return TRUE;
		return FALSE;

	}
	size_t GetMidiDataCount(vector<MIDMUSIC> MIDDATA)
	{
		size_t nArg = MIDDATA.size();
		size_t nCount = 0;
		for (size_t i = 0; i < nArg; i++)
		{


			if (MIDDATA[i].datatype == 2)//
			{

				if (IsValidMidiDataPtr(MIDDATA[i].data))
					nCount++;

			}
			else if (MIDDATA[i].datatype == 0) {//string

				if (IsValidMidiFileName(MIDDATA[i].name))
					nCount++;

			}
			else if (MIDDATA[i].datatype == 1) {//wstring

				if (IsValidMidiFileName(MIDDATA[i].wname)) {
					nCount++;
				}
			}
			else {
			}
		}

		return nCount;


	}
	BOOL GetMidiDataFromPtr(MIDIFILEDATAINFO pData, size_t nIDX)
	{
		pMidiFileData[nIDX].dwSize = pData.dwSize;
		pMidiFileData[nIDX].pData = new BYTE[pData.dwSize];
		if (pMidiFileData[nIDX].pData == NULL)return FALSE;
		memcpy(pMidiFileData[nIDX].pData, pData.pData, pMidiFileData[nIDX].dwSize);
		return TRUE;
	}
	BOOL GetMidiDataFromFile(LPCWSTR pStr, size_t nIDX)
	{
		HANDLE hFile = CreateFileW(pStr,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE,
			0);


		if (hFile != INVALID_HANDLE_VALUE)
		{

			DWORD dwNumOfByteRead;
			INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
			pMidiFileData[nIDX].dwSize = nLen;
			pMidiFileData[nIDX].pData = new BYTE[nLen];
			if (pMidiFileData[nIDX].pData)
			{
				if (ReadFile(hFile, pMidiFileData[nIDX].pData, nLen, &dwNumOfByteRead, 0))
				{
					CloseHandle(hFile);
					return TRUE;
				}
			}
			CloseHandle(hFile);

		}
		pMidiFileData[nIDX].dwSize = 0;
		pMidiFileData[nIDX].pData = NULL;
		return FALSE;

	}
	BOOL GetMidiDataFromFile(LPCSTR pStr, size_t nIDX)
	{
		HANDLE hFile = CreateFileA(pStr,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_ARCHIVE,
			0);


		if (hFile != INVALID_HANDLE_VALUE)
		{

			DWORD dwNumOfByteRead;
			INT nLen = GetFileSize(hFile, &dwNumOfByteRead);
			pMidiFileData[nIDX].dwSize = nLen;
			pMidiFileData[nIDX].pData = new BYTE[nLen];
			if (pMidiFileData[nIDX].pData)
			{
				if (ReadFile(hFile, pMidiFileData[nIDX].pData, nLen, &dwNumOfByteRead, 0))
				{
					CloseHandle(hFile);
					return TRUE;
				}
			}
			CloseHandle(hFile);

		}
		pMidiFileData[nIDX].dwSize = 0;
		pMidiFileData[nIDX].pData = NULL;
		return FALSE;

	}
	size_t GetMidiDataFromArg(vector<MIDMUSIC> MIDDATA)
	{
		size_t nArg = MIDDATA.size();
		size_t nCount = 0;
		size_t nArry = 0;
		for (size_t i = 0; i < nArg; i++)
		{


			if (MIDDATA[i].datatype == 2)//pbyte
			{

				if (IsValidMidiDataPtr(MIDDATA[i].data))
				{
					if (GetMidiDataFromPtr(MIDDATA[i].data, nArry))
						nArry++;
					nCount++;
				}

			}
			else if (MIDDATA[i].datatype == 0) {//string

				if (IsValidMidiFileName(MIDDATA[i].name))
				{
					if (GetMidiDataFromFile(MIDDATA[i].name, nArry))
						nArry++;
					nCount++;
				}

			}
			else if (MIDDATA[i].datatype == 1) {//wstring

				if (IsValidMidiFileName(MIDDATA[i].wname))
				{
					if (GetMidiDataFromFile(MIDDATA[i].wname, nArry))
						nArry++;
					nCount++;
				}

			}

		}
		return nArry;


	}
	void CloseMidiPlayer()
	{
		DestroyMidiPlayer = NULL;
		if (hMidiPlayerThrd)
		{
			TerminateThread(hMidiPlayerThrd, 0);//七号:强制中止线程。这里时候会不会导致闯入文件路径时载入音乐资源无法释放导致的泄露??
			::CloseHandle(hMidiPlayerThrd);
			hMidiPlayerThrd = NULL;
		}

		if (hLoopPlayEvent)
		{
			SetEvent(hLoopPlayEvent);
			::CloseHandle(hLoopPlayEvent);
			hLoopPlayEvent = NULL;
		}


		if (pMidiPlayer)
		{
			delete pMidiPlayer;
			pMidiPlayer = NULL;
		}
		if (pMidiFileData)
		{
			for (size_t i = 0; i < nMidiArrySize; i++)
			{
				if (pMidiFileData[i].pData)
				{
					delete[] pMidiFileData[i].pData;
					pMidiFileData[i].pData = NULL;
					pMidiFileData[i].dwSize = 0;
				}
			}
			delete[] pMidiFileData;
			pMidiFileData = NULL;
			nMidiArrySize = 0;
		}


	}


	DWORD WINAPI  PlayMidiManager(PVOID pParam)
	{

		for (INT n = 0; n < nLoopNum; n++)
		{
			for (size_t i = 0; i < nMidiArrySize; i++)
			{
				if (pMidiFileData[i].pData)
				{
					if (pMidiPlayer)
						delete  pMidiPlayer;
					pMidiPlayer = new CMIDI();
					pMidiPlayer->m_hhLoopPlayEvent = hLoopPlayEvent;
					BOOL bRet = pMidiPlayer->Create(pMidiFileData[i].pData, (DWORD)pMidiFileData[i].dwSize);
					if (bRet)
					{

						bRet = pMidiPlayer->Play();
						if (bRet)
						{
							ResetEvent(hLoopPlayEvent);
							WaitForSingleObject(hLoopPlayEvent, INFINITE);
							Sleep(nPlayWaitTime);
						}

					}
					else {
						delete[] pMidiFileData[i].pData;
						pMidiFileData[i].pData = NULL;
						pMidiFileData[i].dwSize = 0;
					}
				}
			}

		}
		::CloseHandle(hMidiPlayerThrd);
		hMidiPlayerThrd = NULL;
		CloseMidiPlayer();
		return 1;
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, vector<unsigned char> MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 2;
			temp.data.pData = MemData.data();
			temp.data.dwSize = MemData.size();
		}
		else {
			return;
		}

		MidStruct.push_back(temp);
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, wstring MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 1;
			temp.wname = MemData.c_str();
		}
		else {
			return;
		}
		MidStruct.push_back(temp);
	}
	KrnlnApi void PackMid(vector<MIDMUSIC>& MidStruct, string MemData) {
		MIDMUSIC temp;

		if (!MemData.empty())
		{
			temp.datatype = 1;
			temp.name = MemData.c_str();
		}
		else {
			return;
		}
		MidStruct.push_back(temp);
	}
	KrnlnApi void PlayMid(int times, int interval, vector<MIDMUSIC> wannaplay)
	{
		//立即中止播放线程
		CloseMidiPlayer();
		nLoopNum = times;
		if (nLoopNum == -1) {//默认最大播放次数
			nLoopNum = INT_MAX;
		}
		else if (nLoopNum <= 0) {
			return;
		}


		nPlayWaitTime = interval;

		if (nPlayWaitTime < 0) {
			nPlayWaitTime = 0;
		}
		nPlayWaitTime = nPlayWaitTime * 100;
		if (wannaplay.empty())
		{
			return;
		}
		size_t nCount = GetMidiDataCount(wannaplay);//判断有效数据
		if (nCount == 0)
			return;
		pMidiFileData = new MIDIFILEDATAINFO[nCount];
		nCount = GetMidiDataFromArg(wannaplay);
		if (nCount == 0)
		{
			delete[] pMidiFileData;
			pMidiFileData = NULL;
			return;
		}
		nMidiArrySize = nCount;

		hLoopPlayEvent = ::CreateEventW(0, FALSE, FALSE, L"Wait For Midi Play End");

		DWORD dwThreadId;
		HANDLE  hMidiPlayerThrd = CreateThread(NULL,
			0,
			PlayMidiManager,
			0,
			0,
			&dwThreadId);
		if (hMidiPlayerThrd == NULL)
		{
			CloseMidiPlayer();
			return;
		}
		DestroyMidiPlayer = (PDESTROY)CloseMidiPlayer;
	}
}
#endif // 