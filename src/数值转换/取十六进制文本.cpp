#include"string"
using namespace std;
#pragma warning(disable:4996)
#define MIN(a, b)    ((a) < (b) ? (a) : (b)) 



KrnlnApi string 取十六进制文本A(int 欲取进制文本的数值) {
	char pText[16] = { 0 };
	sprintf_s(pText, 16, "%X", 欲取进制文本的数值);
	return pText;
}


KrnlnApi wstring 取十六进制文本W(int 欲取进制文本的数值)
{
	int npReqMinWidth = 0;
	wchar_t psBuf[64] = {};
	const int npBufLength = 64;
	if (npBufLength < sizeof(int) * 8 / 4 + 1)  // 此为缓冲区最小需求尺寸
	{

		return L"";
	}


	wchar_t buf[32] = {};
	wchar_t* ps = buf;
	const wchar_t* psFirstNotZero = NULL;  // 用作记录首个非'0'字符,为NULL表示全部为'0'.

	size_t npShiftBits = sizeof(int) * 8 - 4;

	for (size_t npIndex = 0; npIndex < sizeof(int) * 8 / 4; npIndex++)
	{
		const static wchar_t cs_hex[] =
		{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
		};


		// 获得对应的字符索引
		const size_t npCharIndex = (size_t)((欲取进制文本的数值 >> npShiftBits) & 0x0F);

		// 记录第一个非'0'字符位置
		if (psFirstNotZero == NULL && npCharIndex != 0)
			psFirstNotZero = ps;

		*ps++ = cs_hex[npCharIndex];
		npShiftBits -= 4;
	}
	*ps = '\0';

	const wchar_t* szResult;
	if (npReqMinWidth > 0)  // 设定了最小需求宽度?
	{
		ps -= npReqMinWidth;

		if (ps < buf)
		{
			szResult = buf;
		}
		else if (psFirstNotZero == NULL)
		{
			szResult = ps;
		}
		else
			szResult = MIN(psFirstNotZero, ps);
	}
	else
	{
		if (psFirstNotZero == NULL)
		{
			szResult = L"0";
		}
		else
			szResult = psFirstNotZero;  // 跳过前面所有的'0'字符
	}
	wcscpy(psBuf, szResult);
	return psBuf;
}


