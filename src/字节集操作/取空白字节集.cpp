#include"vector"


/*
返回具有特定数目 0 字节的字节集
<int> 类型变量 <零字节数目>
*/
KrnlnApi std::vector<unsigned char>  取空白字节集(size_t  零字节数目)
{
	if (零字节数目 == 0) {
		return  std::vector<unsigned char>();
	}
	return std::vector<unsigned char>(零字节数目, 0);
}
