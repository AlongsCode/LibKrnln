//此位置为平台系统级常用处理函数,不同平台的提供的代码并不相同，注意区分

#ifdef _WIN32//win环境下的系统处理
#include<windows.h>
BOOL  安装字体(const std::string& 字体文件);
/*当安装字体为内存资源时为临时安装，生命周期跟随进程，并且为进程独占，其他进程须发共享已安装的字体资源*/
HANDLE  安装字体(const vector<unsigned char>& FontData);
BOOL  安装字体(const std::wstring& 字体文件);
BOOL 卸载字体(const std::string& 字体文件);
BOOL 卸载字体(const std::wstring& 字体文件);
BOOL 卸载字体(HANDLE 字体句柄);
BOOL 延迟(INT64 millisecond);
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

#else//Linux POSIX 环境下的系统处理macos用苹果的编程语言比较多，不再单独列出



#endif 

