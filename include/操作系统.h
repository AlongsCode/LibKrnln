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


#else//Linux POSIX 环境下的系统处理macos用苹果的编程语言比较多，不再单独列出



#endif 

