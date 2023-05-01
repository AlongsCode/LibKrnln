
int 取屏幕高度();
int 取屏幕宽度();
void 延时(long long 欲等待的时间);
/*关闭方式：1:#关机;2:#重启;3:#注销;4:#休眠5:#冬眠。注意在Windows95/98/ME下冬眠等同于休眠。*|**/
bool 关闭系统(int 关闭方式 = 1, bool 是否强制执行 = false);
bool 剪辑板可有文本();
//进程名称或窗口标题
bool 终止进程(std::wstring process_name_or_window_title);
//进程名称或窗口标题
bool 终止进程(std::string process_name_or_window_title);
//进程ID
bool 终止进程(unsigned int process_id);

#ifdef _WIN32
bool 是否为64位系统();

class 剪辑板 {
public:
	/*SetClipboardText*/
	inline static  bool 置文本(const std::string& text) {
		if (text.empty()) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		EmptyClipboard();
		const size_t length = text.length() + 1;
		const std::unique_ptr<void, decltype(&GlobalFree)> hMem(reinterpret_cast<void*>(GlobalAlloc(GMEM_MOVEABLE, length)), GlobalFree);
		if (!hMem) {
			return false;
		}
		char* pMem = static_cast<char*>(GlobalLock(hMem.get()));
		if (!pMem) {
			return false;
		}

		strncpy_s(pMem, length, text.c_str(), length);
		GlobalUnlock(hMem.get());
		if (!SetClipboardData(CF_TEXT, hMem.get())) {
			return false;
		}

		return true;
	}
	/*SetClipboardText*/
	inline static  bool 置文本(const std::wstring& text) {
		if (text.empty()) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		EmptyClipboard();
		const size_t length = (text.length() + 1) * sizeof(wchar_t);
		const std::unique_ptr<void, decltype(&GlobalFree)> hMem(GlobalAlloc(GMEM_MOVEABLE, length), GlobalFree);
		if (!hMem) {
			return false;
		}
		wchar_t* pMem = static_cast<wchar_t*>(GlobalLock(hMem.get()));
		if (!pMem) {
			return false;
		}

		wcsncpy_s(pMem, length / sizeof(wchar_t), text.c_str(), length / sizeof(wchar_t));
		GlobalUnlock(hMem.get());
		if (!SetClipboardData(CF_UNICODETEXT, hMem.get())) {
			return false;
		}

		return true;
	}

	/*可拓展的 char wchar_t等*/
	template <typename CharType>
	inline static  std::basic_string<CharType> 取文本()
	{
		std::basic_string<CharType> result;

		if (!IsClipboardFormatAvailable(CF_UNICODETEXT) && !IsClipboardFormatAvailable(CF_TEXT))
		{
			return result;
		}

		if (!OpenClipboard(nullptr))
		{
			return result;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		HANDLE hMem;
		LPVOID pData;
		INT_PTR nSize;
		if (IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			hMem = GetClipboardData(CF_UNICODETEXT);
			if (!hMem)
			{
				return result;
			}
			pData = GlobalLock(hMem);
			if (!pData)
			{
				return result;
			}
			nSize = GlobalSize(hMem);
			result = std::basic_string<CharType>(reinterpret_cast<const CharType*>(pData), nSize / sizeof(CharType));
			GlobalUnlock(hMem);
		}
		else
		{
			hMem = GetClipboardData(CF_TEXT);
			if (!hMem)
			{
				return result;
			}
			pData = GlobalLock(hMem);
			if (!pData)
			{
				return result;
			}
			nSize = GlobalSize(hMem);
			result = std::basic_string<CharType>(reinterpret_cast<const CharType*>(pData), nSize);
			GlobalUnlock(hMem);
		}

		return result;
	}

	/*自定义数据标识，取数据需要*/
	inline static  bool 置数据(const std::vector<unsigned char>& data, const std::wstring& 格式类型)
	{
		if (data.empty()) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		// 注册自定义剪贴板格式
		UINT format = RegisterClipboardFormatW(格式类型.c_str());
		if (format == 0) {
			return false;
		}

		EmptyClipboard();
		const size_t length = data.size();
		const std::unique_ptr<void, decltype(&GlobalFree)> hMem(GlobalAlloc(GMEM_MOVEABLE, length), GlobalFree);
		if (!hMem) {
			return false;
		}

		unsigned char* pMem = static_cast<unsigned char*>(GlobalLock(hMem.get()));
		if (!pMem) {
			return false;
		}

		memcpy_s(pMem, length, data.data(), length);
		GlobalUnlock(hMem.get());
		if (!SetClipboardData(format, hMem.get())) {
			return false;
		}

		return true;
	}

	/*自定义数据标识，取数据需要*/
	inline static  bool 置数据(const std::vector<unsigned char>& data, const std::string& 格式类型)
	{
		if (data.empty()) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		// 注册自定义剪贴板格式
		UINT format = RegisterClipboardFormatA(格式类型.c_str());
		if (format == 0) {
			return false;
		}

		EmptyClipboard();
		const size_t length = data.size();
		const std::unique_ptr<void, decltype(&GlobalFree)> hMem(GlobalAlloc(GMEM_MOVEABLE, length), GlobalFree);
		if (!hMem) {
			return false;
		}

		unsigned char* pMem = static_cast<unsigned char*>(GlobalLock(hMem.get()));
		if (!pMem) {
			return false;
		}

		memcpy_s(pMem, length, data.data(), length);
		GlobalUnlock(hMem.get());
		if (!SetClipboardData(format, hMem.get())) {
			return false;
		}

		return true;
	}

	/*自定义数据标识，取数据需要*/
	inline static  std::vector<unsigned char> 取数据(const std::string& 格式类型)
	{
		std::vector<unsigned char> result;

		if (!OpenClipboard(nullptr))
		{
			return result;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		UINT format = RegisterClipboardFormatA(格式类型.c_str());
		if (!IsClipboardFormatAvailable(format))
		{
			return result;
		}

		HANDLE hMem = GetClipboardData(format);
		if (!hMem)
		{
			return result;
		}

		LPVOID pData = GlobalLock(hMem);
		if (!pData)
		{
			return result;
		}

		INT_PTR nSize = GlobalSize(hMem);
		result.resize(nSize);
		memcpy(result.data(), pData, nSize);
		GlobalUnlock(hMem);

		return result;
	}

	inline  static std::vector<unsigned char> 取数据(const std::wstring& 格式类型)
	{
		std::vector<unsigned char> result;

		if (!OpenClipboard(nullptr))
		{
			return result;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		UINT format = RegisterClipboardFormatW(格式类型.c_str());
		if (!IsClipboardFormatAvailable(format))
		{
			return result;
		}

		HANDLE hMem = GetClipboardData(format);
		if (!hMem)
		{
			return result;
		}

		LPVOID pData = GlobalLock(hMem);
		if (!pData)
		{
			return result;
		}

		INT_PTR nSize = GlobalSize(hMem);
		result.resize(nSize);
		memcpy(result.data(), pData, nSize);
		GlobalUnlock(hMem);

		return result;
	}


	inline static  bool 取数据(const std::wstring& 格式类型, std::vector<unsigned char>& pRet)
	{
		pRet.clear();

		if (!IsClipboardFormatAvailable(RegisterClipboardFormatW(格式类型.c_str()))) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		HANDLE hMem = GetClipboardData(RegisterClipboardFormatW(格式类型.c_str()));
		if (!hMem) {
			return false;
		}

		LPVOID pData = GlobalLock(hMem);
		if (!pData) {
			return false;
		}

		const size_t length = GlobalSize(hMem);
		pRet.resize(length);
		memcpy(pRet.data(), pData, length);
		GlobalUnlock(hMem);

		return true;
	}


	inline static  bool 取数据(const std::string& 格式类型, std::vector<unsigned char>& pRet)
	{
		pRet.clear();

		if (!IsClipboardFormatAvailable(RegisterClipboardFormatA(格式类型.c_str()))) {
			return false;
		}

		if (!OpenClipboard(nullptr)) {
			return false;
		}

		struct ClipboardManager {
			ClipboardManager() {
				OpenClipboard(nullptr);
			}
			~ClipboardManager() {
				CloseClipboard();
			}
		} clipboardManager;

		HANDLE hMem = GetClipboardData(RegisterClipboardFormatA(格式类型.c_str()));
		if (!hMem) {
			return false;
		}

		LPVOID pData = GlobalLock(hMem);
		if (!pData) {
			return false;
		}

		const size_t length = GlobalSize(hMem);
		pRet.resize(length);
		memcpy(pRet.data(), pData, length);
		GlobalUnlock(hMem);

		return true;
	}

	inline  static void 监听(HWND hWnd, WNDPROC lpfnCallback)
	{
		SetPropW(hWnd, L"Clipboard_Monitor", reinterpret_cast<HANDLE>(SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProc_Clipboard_Monitor))));
		SetPropW(hWnd, L"Clipboard_Callback", reinterpret_cast<HANDLE>(lpfnCallback));
		SetPropW(hWnd, L"Clipboard_Viewer", reinterpret_cast<HANDLE>(SetClipboardViewer(hWnd)));
	}

	inline  static void  停止监听(HWND hWnd)//从剪贴板查看器链中删除指定的窗口句柄
	{
		const auto WNDPRC = reinterpret_cast<WNDPROC>(GetPropW(hWnd, L"Clipboard_Monitor"));
		ChangeClipboardChain(hWnd, reinterpret_cast<HWND>(GetPropW(hWnd, L"Clipboard_Viewer")));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WNDPRC));
		RemovePropW(hWnd, L"Clipboard_Monitor");
		RemovePropW(hWnd, L"Clipboard_Callback");
		RemovePropW(hWnd, L"Clipboard_Viewer");
	}
private:
	inline static  LRESULT CALLBACK WndProc_Clipboard_Monitor(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

		const auto WNDPRC = reinterpret_cast<WNDPROC>(GetPropW(hWnd, L"Clipboard_Monitor"));
		const auto call = reinterpret_cast<WNDPROC>(GetPropW(hWnd, L"Clipboard_Callback"));
		const auto viewer = reinterpret_cast<HWND>(GetPropW(hWnd, L"Clipboard_Viewer"));
		switch (uMsg)
		{
		case WM_CHANGECBCHAIN:
		case WM_DESTROY: {
			if (CallWindowProcW(call, hWnd, uMsg, wParam, lParam) == 1) // 拦截
			{
				return 1;
			}
		}break;
		case WM_DRAWCLIPBOARD: {
			if (wParam != reinterpret_cast<WPARAM>(viewer))
			{
				SendMessageW(viewer, uMsg, wParam, lParam);
			}
		}break;
		default:
			break;
		}
		return CallWindowProcW(WNDPRC, hWnd, uMsg, wParam, lParam);
	}

};



#endif // _WIN32
