#pragma once

bool 播放音乐(const vector<unsigned char>& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);
bool 播放音乐(const string& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);
bool 播放音乐(const wstring& 欲播放的音乐, bool 是否循环播放 = false, bool 是否同步播放 = false);

bool 停止播放();


#pragma region 非暴漏接口
namespace KrnlnMidInside {
	struct MIDIFILEDATAINFO
	{
		unsigned char* pData;
		size_t	dwSize;
	};
	//字符串0，宽字符串1，数据指针2;
	struct MIDMUSIC
	{
		union {
			const char* name;
			const wchar_t* wname;
			MIDIFILEDATAINFO data;
		};
		int datatype;
	};
	void PackMid(vector<MIDMUSIC>& MidStruct, string MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, wstring MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, vector<unsigned char> MemData);
	void PlayMid(int times, int interval, vector<MIDMUSIC> wannaplay);
}
#pragma endregion
template <class... T>
void 播放MID(int 播放次数, int 间隔时间, T... 欲播放MID)
{
	vector<KrnlnMidInside::MIDMUSIC> Data;
	std::initializer_list<INT>{(PackMid(Data, std::forward<T>(欲播放MID)), 0)...};
	KrnlnMidInside::PlayMid(播放次数, 间隔时间, Data);
};
