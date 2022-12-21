#include"vector"
using namespace std;
//vector<unsigned char>






/*
返回指定内存指针所指向地址处的一段数据，注意调用本命令前一定要确保所提供的内存地址段真实有效。本命令的最佳使用场合就是在易语言回调子程序和易语言DLL公开子程序用作获取外部数据
<int> 类型变量 <内存数据长度> 本参数提供该内存地址处所需获取的数据长度

*/
KrnlnApi vector<unsigned char> 指针到字节集(void* 内存数据指针, size_t 内存数据长度) {
	return std::vector<unsigned char>((unsigned char*)内存数据指针, (unsigned char*)内存数据指针 + 内存数据长度);
}