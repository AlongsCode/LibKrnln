#pragma once
#ifdef _WIN32

enum class 媒体声道 {
	未知,
	左声道,
	右声道,
	立体声,
	均衡
};
class 媒体播放
{
private:
	std::wstring toLower(const std::wstring& str);
private:
	HWND  m_winHwnd;
	bool m_isVideo;
	std::wstring m_MediaAlias;
public:
	媒体播放();
	~媒体播放();
	bool 打开(const std::wstring& fileName, HWND hWnd = 0);
	bool 是否已打开();
	bool 播放(int position = -1);
	bool 是否为视频();
	HWND 取窗口句柄();
	bool 置窗口句柄(HWND handle);
	//获取当前的播放状态，为以下常量值之一：0、#未知状态；1、#播放状态；2、#停止状态；3、#暂停状态。本命令为初级对象成员命令。* | **| *
	int 取播放状态();
	//单位毫秒
	size_t 取长度();
	long long 取位置();
	size_t 取比率();
	size_t 取帧数();
	bool 暂停();
	bool 继续();
	bool 停止();
	std::wstring 取别名();
	bool 关闭();
	//音量为0-100
	bool 置音量(short 左声道 = -1, short 右声道 = -1);
	//音量为0-100
	bool 取音量(short* 左声道, short* 右声道);

	媒体声道 取媒体声道();

	bool 置媒体声道(媒体声道 type);

	bool 跳到指定帧(size_t 位置, bool 是否立即播放 = false);
	//播放位置必须小于媒体长度，否则可能会造成命令失败。单位：毫秒
	bool 置位置(size_t 位置, bool 是否立即播放 = false);
	//并非所有媒体都支持速度调整,1到2000之间的整数。原始速度为1000。2000为原始速度的2倍，500为原始速度的一半。警告:过慢的速度将导致媒体看起来已经停止了
	bool 置播放速度(int speed);

	int 取播放速度();
	//执行成功返回0，否则返回非零的整数。说明：执行后的实际音量可能最多±2的误差，这里设置的是系统的音量值
	bool 置媒体音量(int  mediaVolume);

	int 取媒体音量();

	size_t 取总时间();

};

#endif // _WIN32
