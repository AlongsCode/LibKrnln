﻿#include"vector"
using namespace std;



//字节集操作 - 取字节集长度
/*
	调用格式： 〈整数型〉 取字节集长度 （字节集 字节集数据） - 系统核心支持库->字节集操作
	英文名称：BinLen
	取字节集型数据的长度。本命令为初级命令。
	参数<1>的名称为“字节集数据”，类型为“字节集（bin）”。参数值指定欲检查其长度的字节集数据。
*/
KrnlnApi size_t 取字节集长度(const vector<unsigned char>& 字节集数据) {//宏代替也可
	return 字节集数据.size();
}