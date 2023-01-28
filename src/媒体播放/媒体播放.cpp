#include<string>
#include<windows.h>
#include <algorithm>
#pragma comment (lib, "winmm.lib")
#pragma warning(disable:28159)
using namespace std;
#define  MCI_RETURN_STRING_SIZE 256
#include"媒体播放.h"

媒体播放::媒体播放() :
	m_winHwnd(NULL),
	m_isVideo(false),
	m_MediaAlias({})
{

};
媒体播放::~媒体播放() {
	关闭();
}
bool 媒体播放::打开(const wstring& fileName, HWND hWnd) {
	if (!m_MediaAlias.empty())
	{
		return true;
	}
	m_MediaAlias = L"Media" + to_wstring(GetTickCount());
	int dotIndex = fileName.rfind(L'.') + 1;
	wstring ileExtension = fileName.substr(dotIndex, 3);
	for (wchar_t& c : ileExtension) {
		c = towlower(c);
	}
	const wchar_t* mediaType = L"MPEGvideo";
	if (ileExtension == L"avi") {
		mediaType = L"avivideo";
	}
	else if (ileExtension == L"wav") {
		mediaType = L"waveaudio";
	}
	else if (ileExtension == L"cda") {
		mediaType = L"cdaudio";
	}
	else if (ileExtension == L"rm" || ileExtension == L"ra" || ileExtension == L"mp" || ileExtension == L"ram" || ileExtension == L"rmvb") {
		mediaType = L"MPEGvideo";
	}
	else if (ileExtension == L"mid" || ileExtension == L"rmi" || ileExtension == L"idi") {
		mediaType = L"Sequencer";
	}
	else if (ileExtension == L"asf" || ileExtension == L"wma" || ileExtension == L"asx" || ileExtension == L"ivf" || ileExtension == L"lsf" || ileExtension == L"lsx" || ileExtension == L"p2v" || ileExtension == L"wax" || ileExtension == L"wvx" || ileExtension == L"wmx" || ileExtension == L"wmp") {
		mediaType = L"MPEGvideo2";
	}
	MCIERROR errorCode = mciSendStringW((L"open " + fileName + L" type " + mediaType + L" alias " + m_MediaAlias + L" style child").c_str(), NULL, 0, hWnd);
	m_isVideo = (ileExtension != L"mp3") && (ileExtension != L"wav") && (ileExtension != L"cda") && (ileExtension != L"mid");
	if (m_isVideo && hWnd) {
		wchar_t buf[64];
		swprintf_s(buf, L"window %s handle %p", m_MediaAlias.c_str(), hWnd);
		if (mciSendStringW(buf, NULL, 0, hWnd) == 0) {
			m_winHwnd = hWnd;
		};
	}
	if (errorCode != 0) {
		return false;
	}
	return true;
}
bool 媒体播放::是否已打开() {
	return !m_MediaAlias.empty();
}

bool 媒体播放::播放(int position)
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	bool error = true;
	wstring command;
	wstring internalCommand;
	if (IsWindow(m_winHwnd))
	{
		command = L"window " + m_MediaAlias + L" handle " + to_wstring((long long)m_winHwnd);
		error = mciSendStringW(command.c_str(), NULL, 0, NULL) == 0;
	}
	if (position == -1)
	{
		internalCommand = L"play " + m_MediaAlias + L" ";
	}
	else
	{
		internalCommand = L"play " + m_MediaAlias + L" from " + to_wstring(position) + L" ";
	}
	bool Ret = !mciSendStringW(internalCommand.c_str(), NULL, 0, NULL) && error;
	return Ret;
}

bool 媒体播放::是否为视频() {
	return 取窗口句柄() != 0;
};
HWND 媒体播放::取窗口句柄()
{
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	std::wstring lpstrCommand;
	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	lpstrCommand = L"status " + m_MediaAlias + L" window handle";
	mciSendStringW(lpstrCommand.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
	long long ret = _wtoll(strReturnString);
	return reinterpret_cast<HWND>(ret);
}

bool 媒体播放::置窗口句柄(HWND handle)
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	if (IsWindow(handle))
	{
		m_winHwnd = handle;
		std::wstring command = L"window " + m_MediaAlias + L" handle " + std::to_wstring((long long)handle);
		MCIERROR ret = mciSendStringW(command.c_str(), 0, 0, 0);
		return ret == 0;
	}
	return false;
};
//获取当前的播放状态，为以下常量值之一：0、#未知状态；1、#播放状态；2、#停止状态；3、#暂停状态。本命令为初级对象成员命令。* | **| *
int 媒体播放::取播放状态()
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	mciSendStringW((L"status " + m_MediaAlias + L" mode").c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
	if (wcscmp(strReturnString, L"playing") == 0) {
		return 1;
	}
	else if (wcscmp(strReturnString, L"stopped") == 0) {
		return 2;
	}
	else if (wcscmp(strReturnString, L"paused") == 0) {
		return 3;
	}
	else {
		return 0;
	}
};
//单位毫秒
size_t 媒体播放::取长度() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	wstring Command;
	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	size_t Ret = 0;
	if (是否为视频()) {
		Command = L"set " + m_MediaAlias + L" time format milliseconds";
	}
	else {
		Command = L"set " + m_MediaAlias + L" time format milliseconds";
	}
	mciSendStringW(Command.c_str(), 0, 0, 0);
	Command = L"status " + m_MediaAlias + L" length";
	if (mciSendStringW(Command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0))
	{
		return 0;
	}
	else
	{
		Ret = _wtoi(strReturnString);
	}
	return  Ret;
};
long long 媒体播放::取位置() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	std::wstring command;
	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	long long Ret = 0;
	command = L"status " + m_MediaAlias + L" position";
	if (mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0))
	{
		Ret = -1;
	}
	else
	{
		Ret = _wtoi(strReturnString);
	}
	return  Ret;
};
size_t 媒体播放::取比率() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	std::wstring command;
	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	size_t Ret = 0;

	if (是否为视频())
	{
		command = L"capability " + m_MediaAlias + L" has video" + L" status " + m_MediaAlias + L" frame rate";
		mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, 0);
		Ret = _wtoi(strReturnString) / 1000;
	}
	return Ret;
};
size_t 媒体播放::取帧数() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	std::wstring command = L"set " + m_MediaAlias + L" time format frames";
	mciSendStringW(command.c_str(), nullptr, 0, nullptr);
	command = L"status " + m_MediaAlias + L" length";

	wchar_t strReturnString[MCI_RETURN_STRING_SIZE] = {};
	if (mciSendStringW(command.c_str(), strReturnString, MCI_RETURN_STRING_SIZE, nullptr))
	{
		return 0;
	}
	else
	{
		return _wtoi(strReturnString);
	}
};
bool 媒体播放::暂停() {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	std::wstring command = L"pause " + m_MediaAlias;
	return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
};
bool 媒体播放::继续() {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	std::wstring command = L"resume " + m_MediaAlias;
	return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
};
bool 媒体播放::停止() {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	std::wstring command = L"stop " + m_MediaAlias;
	if (mciSendStringW(command.c_str(), nullptr, 0, nullptr) != 0) {
		return false;
	}
	command = L"seek " + m_MediaAlias + L" to start";
	return mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
};
wstring 媒体播放::取别名() {
	return m_MediaAlias;
};
size_t 媒体播放::取总时间() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	return 取长度() / 1000;
};
bool 媒体播放::关闭() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	std::wstring command = L"close " + m_MediaAlias;
	if (mciSendStringW(command.c_str(), 0, 0, 0))
	{
		return  false;
	}
	m_winHwnd = NULL;
	m_isVideo = false;
	m_MediaAlias.clear();
	return true;
};
//音量为0-100
bool 媒体播放::置音量(short leftChannelVolume, short rightChannelVolume) {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	MCIERROR leftChannelError = 0;
	MCIERROR rightChannelError = 0;
	bool result = false;
	std::wstring command;
	leftChannelVolume = 10 * leftChannelVolume;
	rightChannelVolume = rightChannelVolume * 10;
	if (leftChannelVolume >= 0 && leftChannelVolume <= 1000) {
		command = L"setaudio " + m_MediaAlias + L" left volume to " + std::to_wstring(leftChannelVolume);
		leftChannelError = mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
	}
	if (rightChannelVolume >= 0 && rightChannelVolume <= 1000)
	{
		command = L"setaudio " + m_MediaAlias + L" right volume to " + std::to_wstring(rightChannelVolume);
		rightChannelError = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
		leftChannelError = leftChannelError && !rightChannelError;
	}
	return leftChannelError;
};
//音量为0-100
bool 媒体播放::取音量(short* leftChannelVolume, short* rightChannelVolume) {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	wchar_t strReturnString[33] = {};
	std::wstring command;
	bool leftChannelSuccess = false;
	bool rightChannelSuccess = false;
	bool Ret = false;
	if (leftChannelVolume)
	{
		command = L"status " + m_MediaAlias + L" left volume";
		leftChannelSuccess = mciSendStringW(command.c_str(), strReturnString, 32, 0) == 0;
		if (leftChannelSuccess)
		{
			*leftChannelVolume = _wtoi(strReturnString) / 10;
		}

	}
	if (rightChannelVolume)
	{
		command = L"status " + m_MediaAlias + L" right volume";
		rightChannelSuccess = mciSendStringW(command.c_str(), strReturnString, 32, 0);
		if (rightChannelSuccess)
		{
			*rightChannelVolume = _wtoi(strReturnString) / 10;
		}
		leftChannelSuccess = leftChannelSuccess && !rightChannelSuccess;
	}
	return leftChannelSuccess;
};
//返回常量中以"声道_"开头的常量值。失败返回0
媒体声道 媒体播放::取媒体声道() {
	if (m_MediaAlias.empty())
	{
		return 媒体声道::未知;
	}
	int result = 0;
	WCHAR channelName[MCI_RETURN_STRING_SIZE] = {};
	std::wstring channelNameLower;
	result = mciSendStringW((L"Status " + m_MediaAlias + L" audio source").c_str(), channelName, MCI_RETURN_STRING_SIZE, 0);
	if (result != 0) {
		return 媒体声道::未知;
	}
	channelNameLower = toLower(channelName);
	if (channelNameLower == L"left") {
		return 媒体声道::左声道;
	}
	else if (channelNameLower == L"right") {
		return 媒体声道::右声道;
	}
	else if (channelNameLower == L"stereo") {
		return  媒体声道::立体声;
	}
	else if (channelNameLower == L"average") {
		return 媒体声道::均衡;
	}
	return 媒体声道::未知;
};
std::wstring 媒体播放::toLower(const std::wstring& str) {
	wstring Ret(str);
	std::transform(str.begin(), str.end(), Ret.begin(), tolower);
	return  Ret;
}
bool 媒体播放::置媒体声道(媒体声道 type) {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	wstring AUDIO;
	switch (type)
	{
	case 媒体声道::左声道:
		AUDIO = L"left";
		break;
	case 媒体声道::右声道:
		AUDIO = L"right";
		break;
	case 媒体声道::立体声:
		AUDIO = L"stereo";
		break;
	case 媒体声道::均衡:
		AUDIO = L"average";
		break;
	default:
		AUDIO = L"left";
		break;
	}
	return mciSendStringW((L"setaudio " + m_MediaAlias + L" source to " + AUDIO).c_str(), 0, 0, 0) == 0;
};

bool 媒体播放::跳到指定帧(size_t framePos, bool playImmediately)
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	MCIERROR result = 0;
	wstring command = L"set " + m_MediaAlias + L" time format frames";
	result = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
	if (result != 0)
	{
		return false;
	}
	command = L"seek " + m_MediaAlias + L" to " + std::to_wstring(framePos);
	result = mciSendStringW(command.c_str(), nullptr, 0, nullptr);
	if (result != 0)
	{
		return false;
	}
	if (playImmediately)
	{
		播放();
	}
	return result == 0;
};
//播放位置必须小于媒体长度，否则可能会造成命令失败。单位：毫秒
bool 媒体播放::置位置(size_t playPosition, bool playImmediately)
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	MCIERROR result = 0;
	result = mciSendStringW((L"set " + m_MediaAlias + L" time format milliseconds").c_str(), nullptr, 0, nullptr);
	if (result != 0)
		return false;
	result = mciSendStringW((L"seek " + m_MediaAlias + L" to " + std::to_wstring(playPosition)).c_str(), nullptr, 0, nullptr);
	if (result != 0)
		return false;
	if (playImmediately)
		播放();
	return result == 0;
}
//并非所有媒体都支持速度调整,1到2000之间的整数。原始速度为1000。2000为原始速度的2倍，500为原始速度的一半。警告:过慢的速度将导致媒体看起来已经停止了
bool 媒体播放::置播放速度(int speed)
{
	if (m_MediaAlias.empty())
	{
		return false;
	}
	if (speed < 1 || speed>2000) {
		return false;
	}
	return mciSendStringW((L"set " + m_MediaAlias + L" speed " + to_wstring(speed)).c_str(), 0, 0, 0) == 0;
}

int 媒体播放::取播放速度() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	wchar_t speedStr[MCI_RETURN_STRING_SIZE] = {};
	mciSendStringW((L"status " + m_MediaAlias + L" speed").c_str(), speedStr, MCI_RETURN_STRING_SIZE, 0);
	return _wtoi(speedStr);
};
//执行成功返回0，否则返回非零的整数。说明：执行后的实际音量可能最多±2的误差，这里设置的是系统的音量值
bool 媒体播放::置媒体音量(int  mediaVolume) {
	if (m_MediaAlias.empty())
	{
		return false;
	}
	if (mediaVolume < 0 || mediaVolume>100) {
		return false;
	}
	std::wstring command = L"setaudio " + m_MediaAlias + L" volume to " + std::to_wstring(mediaVolume * 10);
	return  mciSendStringW(command.c_str(), nullptr, 0, nullptr) == 0;
};

int 媒体播放::取媒体音量() {
	if (m_MediaAlias.empty())
	{
		return 0;
	}
	wchar_t volume[MCI_RETURN_STRING_SIZE];
	bool result = mciSendStringW((L"status " + m_MediaAlias + L" volume").c_str(), volume, MCI_RETURN_STRING_SIZE, 0);
	if (result == 0) {
		return _wtoi(volume) / 10;
	}
	else {
		return -1;
	}

};



