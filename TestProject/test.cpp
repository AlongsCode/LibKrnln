
#define 调试版
#include"..\include\krnln.h"
#pragma warning(disable:4996)



//寻找文本速度对比
//int main() {
//	std::string S = "sadbutsdsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsadstsdsadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsasadsatsdsadsatsdsadsatsdsadsatsdsadsaafsafwaewadsaadt = formatted_text.find(f", N = "tsdsadsatsdsadsatsdsadsaafsafwaewadsaadt = formatted_text.find(f";
//	intptr_t  A, B, ret = 0;
//	size_t i;
//	A = GetTickCount();
//	for (i = 0; i < 9999999; i++)
//	{
//		ret = 寻找文本(S, N, 0, false);
//	}
//	B = GetTickCount();
//	标准输出(0, "速度:" + std::to_string(B - A) + "位置:" + to_string(ret) + " " + std::to_string(i));
//}


//int main() {
//
//	数组 < 文本型 > A = { L"测试",L"测试",L"测试" }, B = { L"测试2" ,L"测试2" ,L"测试2" };
//	调试输出(A + B);
//	return 0;
//}




//int main() {
//	std::vector<int> fruits = { 2,71, 45,11,32, 674,88, 5465,946 ,8676 };
//	数组排序(fruits);
//	int index = 二分查找(fruits, 8676);
//	if (index != -1) {
//		std::cout << "Found cherry at index " << fruits[index] << std::endl;
//	}
//	else {
//		std::cout << "Cherry not found" << std::endl;
//	}
//	return 0;
//}

////在可以的情况西，减少类的继承，增加项目的解耦度和独立性
//class 文件
//{
//public:
//	void* 文件句柄

//};



#pragma region 标准库实现文件读取

#include <chrono>
#include <fstream>

enum class 文件打开方式 {
	读入 = 1,
	写出,
	读写,
	重写,
	改写,
	改读
};


class 文件 {
public:
	std::fstream fs;
	string filename;
	wstring wfilename;
	std::ios::openmode fstreamMode;
	文件() {
		fstreamMode = 0;
	}
	文件(std::wstring 文件路径) :fs(文件路径) {
		fstreamMode = 3;
		if (文件路径.empty())
		{
			return;
		}
		wfilename = 文件路径;
	};
	文件(std::string 文件路径) :fs(文件路径) {
		fstreamMode = 3;
		if (文件路径.empty())
		{
			return;
		}
		filename = 文件路径;
	};
	~文件() {
		if (fs.is_open())
		{
			fs.close();
		}
	}
public:
	bool 打开(std::wstring 文件路径, 文件打开方式 打开方式 = 文件打开方式::读写) {
		if (fs.is_open())
		{
			return false;
		}
		switch (打开方式) {
		case 文件打开方式::读入:
			fstreamMode = std::ios::in;
			break;
		case 文件打开方式::写出:
			fstreamMode = std::ios::out;
			break;
		case 文件打开方式::重写:
			fstreamMode = std::ios::out | std::ios::trunc;
			break;
		case 文件打开方式::改写:
			fstreamMode = std::ios::out | std::ios::app;
			break;
		case 文件打开方式::改读:
			fstreamMode = std::ios::in | std::ios::out | std::ios::app;
			break;
		default: // 读写
			fstreamMode = std::ios::in | std::ios::out;
			break;
		}
		fs.open(文件路径, fstreamMode);
		bool ret = fs.is_open();
		if (ret)
		{
			wfilename = 文件路径;
		}
		return ret;
	}
	bool 打开(std::string 文件路径, 文件打开方式 打开方式 = 文件打开方式::读写) {
		if (fs.is_open())
		{
			return false;
		}

		switch (打开方式) {
		case 文件打开方式::读入:
			fstreamMode = std::ios::in;
			break;
		case 文件打开方式::写出:
			fstreamMode = std::ios::out;
			break;
		case 文件打开方式::重写:
			fstreamMode = std::ios::out | std::ios::trunc;
			break;
		case 文件打开方式::改写:
			fstreamMode = std::ios::out | std::ios::app;
			break;
		case 文件打开方式::改读:
			fstreamMode = std::ios::in | std::ios::out | std::ios::app;
			break;
		default: // 读写
			fstreamMode = std::ios::in | std::ios::out;
			break;
		}
		fs.open(文件路径, fstreamMode);
		bool ret = fs.is_open();
		if (ret)
		{
			filename = 文件路径;
		}
		return ret;
	}
	bool 插入(const void* buffer, size_t length)
	{
		if (!fs.is_open())
		{
			return false;
		}

		// 记录当前文件指针的位置
		std::streampos currPos = fs.tellg();

		// 读取插入位置之后的数据
		std::vector<char> endData((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

		// 将文件指针设置回当前位置
		fs.seekg(currPos, std::ios::beg);

		// 写入 buffer 中的数据
		fs.write(static_cast<const char*>(buffer), length);

		// 写入插入位置之后的数据
		fs.write(endData.data(), endData.size());

		// 将文件指针设置回当前插入数据尾
		fs.seekg((intptr_t)currPos + length, std::ios::beg);

		return true;
	}
	bool 锁住(size_t 欲加锁的位置, size_t 欲加锁的长度, intptr_t 加锁重试时间) {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.rdbuf()->pubseekoff(欲加锁的位置, std::ios::beg);
			if (加锁重试时间) {
				if (加锁重试时间 == -1) {
					fs.rdbuf()->sputn(nullptr, 欲加锁的长度);
				}
				else if (加锁重试时间 > 0) {
					auto start = std::chrono::steady_clock::now();
					bool success = false;
					do {
						fs.rdbuf()->sputn(nullptr, 欲加锁的长度);
						success = fs.good();
						auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
							std::chrono::steady_clock::now() - start
							);
						if (elapsed.count() > 加锁重试时间) {
							break;
						}
					} while (!success);
					return success;
				}
			}
			else {
				fs.rdbuf()->sputn(nullptr, 欲加锁的长度);
				return fs.good();
			}
		}
		catch (const std::ios_base::failure&) {
			return false;
		}
		return false;
	}
	bool 解锁(size_t 欲解锁的位置, size_t 欲解锁的长度) {

		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.rdbuf()->pubseekoff(欲解锁的位置, std::ios::beg);
			fs.rdbuf()->sputn(nullptr, 欲解锁的长度);
			return fs.good();
		}
		catch (const std::ios_base::failure&) {
			return false;
		}
		return false;
	}
	void 关闭() {
		if (fs.is_open())
		{
			fs.close();
		}
	}
	vector<unsigned char> 读入字节集(size_t 读入长度)
	{
		if (!fs.is_open())
		{
			return {};
		}
		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try
		{	//记录当前指针
			auto curPos = fs.tellg();
			// 获取文件大小
			fs.seekg(0, std::ios::end);
			auto fileSize = fs.tellg();
			//回到记录指针
			fs.seekg(curPos, std::ios::beg);
			// 如果当前指针位置加上读入长度大于文件大小，则将读入长度设置为文件大小减去当前指针位置
			if ((size_t)curPos + 读入长度 > (size_t)fileSize)
			{
				读入长度 = static_cast<size_t>(fileSize - curPos);
			}
			cout << 读入长度;
			vector<unsigned char> ret;
			ret.resize(读入长度);
			fs.read((char*)&ret[0], 读入长度);
			return ret;
		}
		catch (const std::ios_base::failure&)
		{
			return {};
		}
	}
	std::string 读入文本A(size_t 文本长度)
	{
		if (!fs.is_open())
		{
			return "";
		}
		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try
		{	//记录当前指针
			std::streampos curPos = fs.tellg();
			// 获取文件大小
			fs.seekg(0, std::ios::end);
			std::streampos fileSize = fs.tellg();
			//回到记录指针
			fs.seekg(curPos, std::ios::beg);
			// 如果当前指针位置加上读入长度大于文件大小，则将读入长度设置为文件大小减去当前指针位置
			if ((size_t)curPos + 文本长度 > (size_t)fileSize)
			{
				文本长度 = static_cast<size_t>(fileSize - curPos);
			}

			std::string ret;
			ret.resize(文本长度);
			fs.read(&ret[0], 文本长度);
			return ret;
		}
		catch (const std::ios_base::failure&)
		{
			return "";
		}
	}

	std::wstring 读入文本W(size_t 文本长度)
	{
		if (!fs.is_open())
		{
			return L"";
		}
		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try
		{	//记录当前指针
			std::streampos curPos = fs.tellg();
			// 获取文件大小
			fs.seekg(0, std::ios::end);
			std::streampos fileSize = fs.tellg();
			//回到记录指针
			fs.seekg(curPos, std::ios::beg);
			// 如果当前指针位置加上读入长度大于文件大小，则将读入长度设置为文件大小减去当前指针位置
			intptr_t needlen = (intptr_t)curPos + 文本长度 * sizeof(wchar_t);
			if (needlen > (intptr_t)fileSize)
			{
				needlen = static_cast<size_t>(fileSize - curPos);
			}

			std::wstring ret;
			intptr_t wlen = needlen / sizeof(wchar_t);
			ret.resize(wlen);
			fs.read((char*)&ret[0], wlen * sizeof(wchar_t));
			return ret;
		}
		catch (const std::ios_base::failure&)
		{
			return L"";
		}
	}

	bool 写(const vector<unsigned char>& 缓冲区) {
		if (!fs.is_open()) {
			return false;
		}
		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.write(reinterpret_cast<const char*>(缓冲区.data()), 缓冲区.size());
		}
		catch (...) {
			return false;
		}
		return true;
	}
	bool 写(const string& 缓冲区) {
		if (!fs.is_open()) {
			return false;
		}
		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.write(缓冲区.data(), 缓冲区.size());
		}
		catch (...) {
			return false;
		}
		return true;
	}
	std::string 读入一行A() {
		std::string 文本行;
		if (!fs.is_open()) {
			return {};
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			std::getline(fs, 文本行);
		}
		catch (...) {
			return {};
		}
		return 文本行;
	}
	bool 写入文本行(const std::string& 文本行) {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs << 文本行 << std::endl;
		}
		catch (...) {
			return false;
		}
		return true;
	}
	std::string 读取文本() {
		std::string 文本;
		if (!fs.is_open()) {
			return {};
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.seekg(0, std::ios::end);
			auto size = fs.tellg();
			if (size > 0) {
				fs.seekg(0, std::ios::beg);
				文本.resize(static_cast<size_t>(size));
				fs.read(&文本[0], size);
			}
			else {
				文本.clear();
			}
		}
		catch (...) {
			return {};
		}
		return 文本;
	}
	//从给定下标开始，将指针移动到指定位数移动后的下标的位置上，例如移动到文件首为0。
	bool 移动读写位置(文件读写位置 起始移动位置, intptr_t 移动距离) {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			std::ios::seekdir seekDir;
			switch (起始移动位置) {
			case 文件读写位置::文件尾:
				seekDir = std::ios::end;
				break;
			case 文件读写位置::现行位置:
				seekDir = std::ios::cur;
				break;
			default: // 文件首
				seekDir = std::ios::beg;
			}
			fs.seekp(移动距离, seekDir);
			return fs.good();
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return false;
		}
		return false;
	}
	bool 移动读写位置(intptr_t 移动的长度, 文件读写位置 whence = 文件读写位置::现行位置) {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			std::ios::seekdir seekDir;
			switch (whence) {
			case 文件读写位置::文件首:
				seekDir = std::ios::beg;
				break;
			case 文件读写位置::文件尾:
				seekDir = std::ios::end;
				break;
			case 文件读写位置::现行位置:
				seekDir = std::ios::cur;
				break;
			default:
				return false;
			}
			fs.seekp(移动的长度, seekDir);
			return fs.good();
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return false;
		}
		return false;
	}
	//移动到文件起始下标。
	bool 移动到文件首() {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.seekp(0, std::ios::beg);
			return fs.good();
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return false;
		}
		return false;
	}
	intptr_t 取读写位置() {
		if (!fs.is_open()) {
			return -1;
		}

		//fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			return fs.tellp();
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return -1;
		}
	}
	//移动到文件尾字符以后的下标
	bool 移动到文件尾() {
		if (!fs.is_open()) {
			return false;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			fs.seekp(0, std::ios::end);
			return fs.good();
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return false;
		}
		return false;
	}
	intptr_t 取文件长度() {
		if (!fs.is_open()) {
			return -1;
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			//记录读写位置
			auto cur = fs.tellp();
			//移至文件尾
			fs.seekp(0, std::ios::end);
			intptr_t ret = fs.tellp();
			cout << ret;
			//回到位置
			fs.seekp(cur, std::ios::beg);
			return ret;
		}
		catch (const std::ios_base::failure&) {
			// 处理异常
			return -1;
		}
		return -1;
	}
	std::wstring 读入一行W()
	{
		wstring pszRet;

		if (!fs.is_open()) {
			return L"";
		}

		fs.exceptions(std::ios::failbit | std::ios::badbit);
		try {
			// 获取当前文件指针的位置
			size_t orgLoc = fs.tellp();
			// 声明一个用于存储读取字节数的变量
			size_t dwNumOfByteRead = 0;
			// 获取文件大小，减去当前文件指针的位置，得到剩余的字节数
			size_t nLen = 取文件长度() - orgLoc;
			// 声明一个用于存储数据块的 vector 变量
			vector<vector<char>>  vecMEMSP;
			// 声明一个用于存储已读取字节数的变量
			size_t nTLen = 0;
			// 通过循环，每次读取 4096 个字节的数据块
			for (size_t i = 0; i < nLen; i++)
			{
				vector<unsigned char> pData = 读入字节集(min(nLen - i, 4096));
			}

		}
		catch (const std::ios_base::failure&) {
			return L"";
		}
		return pszRet;
	}
private:
	wfstream convert_to_wfstream()
	{
		// 获取fstream对象的各类信息
		//打开方式


		//当前指针偏移
		auto off = fs.tellg();
		// 关闭原来的fstream对象
		fs.close();
		// 打开一个宽字符文本文件

		wfstream wfs;
		if (!filename.empty())
		{
			wfs.open(filename, fstreamMode);

		}
		else
		{
			wfs.open(wfilename, fstreamMode);
		}
		if (wfs.is_open())
		{

			//移动到指定偏移
			wfs.seekg(off, std::ios::beg);
		}
		return wfs;
	}

	void return_fstream(wfstream& wfs)
	{
		// 获取fstream对象的各类信息
		//打开方式
		//当前指针偏移
		auto off = wfs.tellg();
		// 关闭临时的wfstream对象
		wfs.close();
		// 打开单字节读取文件流
		if (!filename.empty())
		{
			fs.open(filename, fstreamMode);

		}
		else
		{
			fs.open(wfilename, fstreamMode);
		}
		//移动到指定偏移
		fs.seekg(off, std::ios::beg);
	}
};
#pragma endregion







int main()
{
	内存文件 A;
	A.写(L"test", 2);
	//调试输出(到字节集(L"test"), 到字节集("test"));
	//调试输出(A.取文件长度());
	//调试输出(A.获取位置());
	A.移到文件首();
	调试输出(A.读(999));
	return 0;
}
