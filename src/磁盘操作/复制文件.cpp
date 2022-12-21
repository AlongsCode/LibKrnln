#include<string>









#ifdef _WIN32
#include<windows.h>
using namespace std;
KrnlnApi bool 复制文件(const string& 被复制的文件名, const string& 复制到的文件名) {
	return CopyFileA(被复制的文件名.c_str(), 复制到的文件名.c_str(), FALSE);
}
KrnlnApi bool 复制文件(const wstring& 被复制的文件名, const wstring& 复制到的文件名) {
	return CopyFileW(被复制的文件名.c_str(), 复制到的文件名.c_str(), FALSE);
}
#else //linux 文件流 
#include <fstream>  
KrnlnApi bool 复制文件(const wstring& 被复制的文件名, const wstring& 复制到的文件名)
{

	ifstream infile(被复制的文件名, ios::in | ios::binary);//二进制形式打开
	if (infile.is_open() == 0) {//出错处理
		return 0;
	}
	ofstream outfile(复制到的文件名, ios::out | ios::binary);//二进制形式打开
	if (outfile.is_open() == 0) {//出错处理
		infile.close();//记得关闭
		return 0;
	}
	//开始读写
	const int FLUSH_NUM = 1024 * 1024;//缓冲区大小设置为1M
	char* ch = new(nothrow)char[FLUSH_NUM];
	if (ch == NULL) {//出错处理
		infile.close();//记得关闭
		outfile.close();//记得关闭
		return 0;
	}
	while (!infile.eof()) {
		infile.read(ch, FLUSH_NUM);
		outfile.write(ch, infile.gcount());//写入读入的成功个数
	}
	delete[]ch;//记得释放
	infile.close();//记得关闭
	outfile.close();//记得关闭
	return 1;
}
KrnlnApi bool 复制文件(const string& 被复制的文件名, const string& 复制到的文件名)
{

	ifstream infile(被复制的文件名, ios::in | ios::binary);//二进制形式打开
	if (infile.is_open() == 0) {//出错处理
		return 0;
	}
	ofstream outfile(复制到的文件名, ios::out | ios::binary);//二进制形式打开
	if (outfile.is_open() == 0) {//出错处理
		infile.close();//记得关闭
		return 0;
	}
	//开始读写
	const int FLUSH_NUM = 1024 * 1024;//缓冲区大小设置为1M
	char* ch = new(nothrow)char[FLUSH_NUM];
	if (ch == NULL) {//出错处理
		infile.close();//记得关闭
		outfile.close();//记得关闭
		return 0;
	}
	while (!infile.eof()) {
		infile.read(ch, FLUSH_NUM);
		outfile.write(ch, infile.gcount());//写入读入的成功个数
	}
	delete[]ch;//记得释放
	infile.close();//记得关闭
	outfile.close();//记得关闭
	return 1;
}
#endif