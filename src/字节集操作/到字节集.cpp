
#include"string"
#include"vector"
using namespace std;

/*
将指定数据转换为字节集后返回转换结果
<void*> 类型变量 <欲转换为字节集的数据> 参数值只能为基本数据类型数据或数值型数组

*/

KrnlnApi vector<unsigned char> 到字节集(char* 欲转换为字节集的数据) {
	if (欲转换为字节集的数据 == nullptr) {
		// 如果输入为空指针，直接返回一个空 vector
		return {};
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据, (unsigned char*)欲转换为字节集的数据 + strlen(欲转换为字节集的数据) * sizeof(char));//为了和易保持同步,没有添加结束符'\0'
}
KrnlnApi vector<unsigned char> 到字节集(const char* 欲转换为字节集的数据) {
	if (欲转换为字节集的数据 == nullptr) {
		// 如果输入为空指针，直接返回一个空 vector
		return {};
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据, (unsigned char*)欲转换为字节集的数据 + strlen(欲转换为字节集的数据) * sizeof(char));//为了和易保持同步,没有添加结束符'\0'
}
KrnlnApi vector<unsigned char> 到字节集(const wchar_t* 欲转换为字节集的数据) {
	if (欲转换为字节集的数据 == nullptr) {
		// 如果输入为空指针，直接返回一个空 vector
		return {};
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据, (unsigned char*)欲转换为字节集的数据 + wcslen(欲转换为字节集的数据) * sizeof(wchar_t));//为了和易保持同步,没有添加结束符'\0'
}
KrnlnApi vector<unsigned char> 到字节集(wchar_t* 欲转换为字节集的数据) {
	if (欲转换为字节集的数据 == nullptr) {
		// 如果输入为空指针，直接返回一个空 vector
		return {};
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据, (unsigned char*)欲转换为字节集的数据 + wcslen(欲转换为字节集的数据) * sizeof(wchar_t));//为了和易保持同步,没有添加结束符'\0'
}



KrnlnApi vector<unsigned char> 到字节集(const std::string& 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		// 如果输入为空字符串，直接返回一个空 vector
		return {};
	}
	size_t len = 欲转换为字节集的数据.size();
	std::vector<unsigned char> byte_array(len * sizeof(char));
	std::memcpy(byte_array.data(), 欲转换为字节集的数据.c_str(), len * sizeof(char));
	return byte_array;

}

KrnlnApi vector<unsigned char> 到字节集(const std::wstring& 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		// 如果输入为空字符串，直接返回一个空 vector
		return {};
	}
	size_t len = 欲转换为字节集的数据.size();
	std::vector<unsigned char> byte_array(len * sizeof(wchar_t));
	std::memcpy(byte_array.data(), 欲转换为字节集的数据.c_str(), len * sizeof(wchar_t));
	return byte_array;
}


KrnlnApi vector<unsigned char> 到字节集(unsigned char 欲转换为字节集的数据) {
	return vector<unsigned char>({ 欲转换为字节集的数据 });
}
KrnlnApi vector<unsigned char> 到字节集(int 欲转换为字节集的数据) {
	return vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据) + sizeof(int));
}
KrnlnApi vector<unsigned char> 到字节集(short 欲转换为字节集的数据) {
	return vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据) + sizeof(short));
}
KrnlnApi vector<unsigned char> 到字节集(long long 欲转换为字节集的数据) {

	return vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据) + sizeof(long long));
}
KrnlnApi vector<unsigned char> 到字节集(float 欲转换为字节集的数据) {
	return vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据) + sizeof(float));
}
KrnlnApi vector<unsigned char> 到字节集(double 欲转换为字节集的数据) {
	return vector<unsigned char>((unsigned char*)&欲转换为字节集的数据, ((unsigned char*)&欲转换为字节集的数据) + sizeof(double));
}


KrnlnApi vector<unsigned char> 到字节集(vector<unsigned char> 欲转换为字节集的数据) {
	return 欲转换为字节集的数据;

}


KrnlnApi vector<unsigned char> 到字节集(std::vector<int> 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		return vector<unsigned char>();
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)&欲转换为字节集的数据) + 欲转换为字节集的数据.capacity() * sizeof(int));
}

KrnlnApi vector<unsigned char> 到字节集(std::vector<float> 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		return vector<unsigned char>();
	}

	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)欲转换为字节集的数据.data() + 欲转换为字节集的数据.capacity() * sizeof(float)));
}
KrnlnApi vector<unsigned char> 到字节集(std::vector<double> 欲转换为字节集的数据) {
	if (欲转换为字节集的数据.empty()) {
		return vector<unsigned char>();
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)欲转换为字节集的数据.data() + 欲转换为字节集的数据.capacity() * sizeof(double)));

}
KrnlnApi vector<unsigned char> 到字节集(std::vector<long long> 欲转换为字节集的数据) {

	if (欲转换为字节集的数据.empty()) {
		return vector<unsigned char>();
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)欲转换为字节集的数据.data() + 欲转换为字节集的数据.capacity() * sizeof(long long)));
}
KrnlnApi vector<unsigned char> 到字节集(std::vector<short> 欲转换为字节集的数据) {

	if (欲转换为字节集的数据.empty()) {
		return vector<unsigned char>();
	}
	return vector<unsigned char>((unsigned char*)欲转换为字节集的数据.data(), ((unsigned char*)欲转换为字节集的数据.data() + 欲转换为字节集的数据.capacity() * sizeof(short)));
}
