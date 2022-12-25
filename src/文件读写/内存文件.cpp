#include<string>
#include <vector>
#include <cstring>
#include <cstdlib>




enum class 内存文件操作命令 {
	读入缓冲区,
	写入缓冲区,
	提交缓冲区,
	检查缓冲区
};
enum  class 读写位置移动方向
{
	前 = 0,
	后 = 1,
};
enum class 文件读写位置
{
	文件首 = 1,
	文件尾,
	现行位置
};



class KrnlnApi 内存文件
{
private:
	std::vector<unsigned char> 数据; // 储存文件数据
	size_t 当前位置; // 当前读写位置
	size_t 文件大小; // 文件长度
	// 改变缓冲区长度
	void 改变缓冲区长度(size_t 新长度);

public:
	// 初始化内存文件，可以指定 vector 的初始容量
	内存文件(size_t grow_bytes = 1024);

	~内存文件();
	//
	void 关闭();
	// 读取数据
	std::vector<unsigned char> 读(size_t 读入长度);
	//写入数据
	void 写();
	void 写(const std::vector<unsigned char>& data);
	void 写(const std::string& data);
	void 写(const std::wstring& data);
	void 写(char* data);
	void 写(wchar_t* data);
	void 写(const char* data);
	void 写(const wchar_t* data);
	template<typename T, typename ... Args>
	void 写(const T& data) {
		写(vector<unsigned char>((unsigned char*)&data, ((unsigned char*)&data + sizeof(T))));
	}
	template<typename T, typename ... Args>
	void 写(const T& data, const Args&...args) {
		写(data);
		写(args...);
	}

	//插入数据
	bool 插入(std::vector<unsigned char> data);

	// 移动读写位置
	bool 移动读写位置(long offset, 文件读写位置 origin = 文件读写位置::现行位置);

	// 移动到文件开头
	void 移到文件首();

	// 移动到文件末尾
	void 移到文件尾();

	// 设置文件长度
	void 置文件大小(size_t 新长度);
	// 获取文件长度
	size_t 获取长度() const;

	// 获取当前读写位置
	size_t 获取位置() const;


};





内存文件::内存文件(size_t grow_bytes) : 数据(grow_bytes), 当前位置(0), 文件大小(0) {}
void 内存文件::改变缓冲区长度(size_t 新长度)
{
	if (新长度 > 数据.size())
	{
		数据.resize(新长度);
	}
}
// 初始化内存文件，可以指定 vector 的初始容量

内存文件::~内存文件() { 关闭(); }
//
void 内存文件::关闭()
{

	数据.resize(0);
	当前位置 = 0;
	文件大小 = 0;

}
// 读取数据
std::vector<unsigned char> 内存文件::读(size_t 读入长度)
{
	// 如果读入长度为0，则返回一个空的 vector
	if (读入长度 == 0)
	{
		return std::vector<unsigned char>();
	}
	// 如果当前位置已经超出文件长度，则返回一个空的 vector
	if (当前位置 > 文件大小)
	{
		return std::vector<unsigned char>();
	}

	// 计算实际读入的字节数
	size_t 实际读入长度;
	if (当前位置 + 读入长度 > 文件大小)
	{
		实际读入长度 = 文件大小 - 当前位置;
	}
	else
	{
		实际读入长度 = 读入长度;
	}
	// 从数据中提取出需要读入的数据，并将当前位置移动到读入位置的后面
	std::vector<unsigned char> ret(数据.begin() + 当前位置, 数据.begin() + 当前位置 + 实际读入长度);
	当前位置 += 实际读入长度;
	return ret;
}
//写入数据
void 内存文件::写() {
	//出口
}
void 内存文件::写(const std::vector<unsigned char>& data)
{

	// 如果 data 为空，则什么也不做
	if (data.empty())
	{
		return;
	}
	// 如果缓冲区的长度不够，则改变缓冲区的长度
	if (当前位置 + data.size() > 数据.size())
	{
		改变缓冲区长度(当前位置 + data.size());
	}

	// 将 data 拷贝到缓冲区中
	std::copy(data.begin(), data.end(), 数据.begin() + 当前位置);
	当前位置 += data.size();

	// 更新文件大小
	if (当前位置 > 文件大小)
	{
		文件大小 = 当前位置;
	}
}
void 内存文件::写(const std::string& data)
{

	// 将 string 转换为 vector<unsigned char> 类型
	std::vector<unsigned char> data_vec(data.begin(), data.end());
	// 调用 vector 版本的写函数
	写(data_vec);
}
void 内存文件::写(const std::wstring& data)
{
	// 将 wstring 转换为 vector<unsigned char> 类型
	std::vector<unsigned char> data_vec(data.begin(), data.end());
	// 调用 vector 版本的写函数
	写(data_vec);
}
void 内存文件::写(char* data) {
	写(std::vector<unsigned char>((unsigned char*)data, (unsigned char*)data + strlen(data) * sizeof(char)));
}
void 内存文件::写(wchar_t* data) {
	写(std::vector<unsigned char>((unsigned char*)data, (unsigned char*)data + wcslen(data) * sizeof(wchar_t)));
}
void 内存文件::写(const char* data) {
	写(std::vector<unsigned char>((unsigned char*)data, (unsigned char*)data + strlen(data) * sizeof(char)));
}
void 内存文件::写(const wchar_t* data) {
	写(std::vector<unsigned char>((unsigned char*)data, (unsigned char*)data + wcslen(data) * sizeof(wchar_t)));
}


//插入数据
bool 内存文件::插入(std::vector<unsigned char> data)
{
	// 如果要插入的数据为空，则返回 false
	if (data.empty())
	{
		return false;
	}

	// 在当前位置插入数据
	数据.insert(数据.begin() + 当前位置, data.begin(), data.end());
	// 将当前位置移动到插入后的位置
	当前位置 += data.size();
	// 更新文件大小
	if (当前位置 > 文件大小)
	{
		文件大小 = 当前位置;
	}

	return true;
}

// 移动读写位置
bool 内存文件::移动读写位置(long offset, 文件读写位置 origin)
{
	bool success = false;
	size_t 新位置;
	switch (origin)
	{
	case 文件读写位置::文件首:
		新位置 = offset;
		break;
	case 文件读写位置::现行位置:
		新位置 = 当前位置 + offset;
		break;
	case 文件读写位置::文件尾:
		新位置 = 文件大小 + offset;
		break;
	default:
		return success;
	}
	if (新位置 > 文件大小)
	{

		新位置 = 文件大小;
	}
	else if (新位置 < 0)
	{
		新位置 = 0;
	}
	当前位置 = 新位置;
	success = true;
	return success;
}

// 移动到文件开头
void 内存文件::移到文件首()
{
	当前位置 = 0;
}

// 移动到文件末尾
void 内存文件::移到文件尾()
{
	当前位置 = 文件大小;
}

// 设置文件长度
void 内存文件::置文件大小(size_t 新长度)
{
	if (新长度 > 数据.size())
	{//扩容缓冲区
		数据.resize(新长度);
	}
	文件大小 = 新长度;
	if (当前位置 > 文件大小)
	{
		当前位置 = 文件大小;
	}
}
// 获取文件长度
size_t 内存文件::获取长度() const
{
	return 文件大小;
}

// 获取当前读写位置
size_t 内存文件::获取位置() const
{
	return 当前位置;
}

