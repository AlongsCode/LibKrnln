#pragma warning(disable:26451)
#include<string>
KrnlnApi std::wstring 阶乘(uint64_t x)
{
	std::wstring result = L"1";
	for (uint64_t i = 2; i <= x; i++) {
		std::wstring tmp = std::to_wstring(i);
		int carry = 0;
		for (uint64_t j = 0; j < result.size() || j < tmp.size() || carry > 0; j++) {
			if (j < result.size()) {
				carry += result[result.size() - 1 - j] - L'0';
			}
			if (j < tmp.size()) {
				carry += tmp[tmp.size() - 1 - j] - L'0';
			}
			result[result.size() - 1 - j] = (carry % 10) + L'0';
			carry /= 10;
		}
		if (carry > 0) {
			result = wchar_t(carry + L'0') + result;
		}
	}
	return result;
}


KrnlnApi std::wstring 双阶乘(uint64_t x)
{
	std::wstring result = L"1";
	for (uint64_t i = 2; i <= x; i += 2) {
		std::string tmp = std::to_string(i / (i - 1));
		uint64_t carry = 0;
		for (uint64_t j = 0; j < result.size() || j < tmp.size() || carry > 0; j++) {
			if (j < result.size()) {
				carry += result[result.size() - 1 - j] - L'0';
			}
			if (j < tmp.size()) {
				carry += tmp[tmp.size() - 1 - j] - L'0';
			}
			result[result.size() - 1 - j] = (carry % 10) + L'0';
			carry /= 10;
		}
		if (carry > 0) {
			result = wchar_t(carry + L'0') + result;
		}
	}
	return result;
}