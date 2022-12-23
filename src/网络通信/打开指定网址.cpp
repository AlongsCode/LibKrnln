#include<string>


using namespace std;

KrnlnApi void 打开指定网址(const string& url)
{
#ifdef _WIN32
	const string OPEN_COMMAND = "start ";
#elif __APPLE__
	const string OPEN_COMMAND = "open ";
#else
	const string OPEN_COMMAND = "xdg-open ";
#endif
	string command = OPEN_COMMAND + url;
	system(command.c_str());
}
KrnlnApi void 打开指定网址(const wstring& url)
{
#ifdef _WIN32
	const wstring OPEN_COMMAND = L"start ";
#elif APPLE
	const wstring OPEN_COMMAND = L"open ";
#else
	const wstring OPEN_COMMAND = L"xdg-open ";
#endif
	wstring command = OPEN_COMMAND + url;
	_wsystem(command.c_str());
}




