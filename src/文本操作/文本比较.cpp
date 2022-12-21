#include"string"
using namespace std;




/*
如果返回值小于0，表示文本一小于文本二；如果等于0，表示文本一等于文本二；如果大于0，表示文本一大于文本二。如果比较时区分大小写，也可以使用比较运算符进行同样的操作
<bool> 类型变量 <是否区分大小写> 为真区分大小写，为假不区分

*/
KrnlnApi int 文本比较(const string& 待比较文本一, const string& 待比较文本二, bool 是否区分大小写) {

	if (是否区分大小写) {//区分大小写
		return strcmp(待比较文本一.c_str(), 待比较文本二.c_str());

	}
	return _stricmp(待比较文本一.c_str(), 待比较文本二.c_str());
}
KrnlnApi int 文本比较(const  wstring& 待比较文本一, const  wstring& 待比较文本二, bool 是否区分大小写) {

	if (是否区分大小写) {//区分大小写
		return wcscmp(待比较文本一.c_str(), 待比较文本二.c_str());
	}
	return _wcsicmp(待比较文本一.c_str(), 待比较文本二.c_str());
}