#include<string>
#include"文本转换.h"
#pragma warning(disable:4996)
using namespace std;






#define  IsDoubleEqualZero(db) (db >= -1e-6 && db <= 1e-6f)

inline const wchar_t* N64ToStr(long long n64, wchar_t* psBuf, const int npBufLength)
{


	if (npBufLength < 26)  // 26为最小需求尺寸(可能能更小,但是无需太精确)
		return (L"");

	if (n64 == 0)
	{
		psBuf[0] = '0';
		psBuf[1] = '\0';
		return psBuf;
	}

	if (n64 == INT64_MIN)  // 此值在下面转换为正数时会失败
		return (L"-9223372036854775808");

	//----------------------------------------------------

	wchar_t buf[32];
	wchar_t* ps = &buf[31];
	*ps-- = '\0';

	const bool blpIsNeg = (n64 < 0);  // 获得是否为负数
	if (blpIsNeg)
		n64 = -n64;  // 将负数转换为正数


	while (n64 > 0)
	{

		*ps-- = (n64 % 10) + '0';
		n64 /= 10;
	}


	if (blpIsNeg)
		*ps = '-';
	else
		ps++;

	wcscpy(psBuf, ps);
	return psBuf;
}

KrnlnApi wstring 数值到大写W(double 欲转换形式的数值, bool 是否转换为简体)
{
	wstring strConvertResult;
	const wchar_t* szNumber;
	const wchar_t* szUnit;
	if (是否转换为简体)
	{
		szNumber = L"零一二三四五六七八九";
		szUnit = L"十百千万十百千亿十百千万";
	}
	else
	{
		szNumber = L"零壹贰叁肆伍陆柒捌玖";
		szUnit = L"拾佰仟万拾佰仟亿拾佰仟万";
	}

	wchar_t buf[128] = { 0 };
	wchar_t* psBuf = buf;

	const bool blpNeg = (欲转换形式的数值 < 0);
	if (blpNeg)
		欲转换形式的数值 = -欲转换形式的数值;

	if (IsDoubleEqualZero(欲转换形式的数值))
	{
		*psBuf = szNumber[0];
		psBuf[1] = '\0';
	}
	else if (欲转换形式的数值 > 9999999999999.0)
	{
		wcscpy(psBuf, L"溢出");
	}
	else
	{
		psBuf = &buf[127];
		*psBuf = '\0';

		double dbMod = modf(欲转换形式的数值, &欲转换形式的数值);
		dbMod *= 100;
		if (modf(dbMod + 1e-6, &dbMod) >= 0.5)
			dbMod++;

		long long n64 = (long long)欲转换形式的数值;
		long long npMod = (long long)dbMod;

		if (npMod >= 100)
		{
			n64++;
		}
		else if (npMod != 0)
		{
			wchar_t buf1[32], buf2[32];
			wchar_t* psNumber = (wchar_t*)N64ToStr(npMod + 100, buf1, 32);

			wchar_t* ps = psNumber + wcslen(psNumber) - 1;
			psNumber[0] = '\0';
			while (*ps == '0')
				*ps-- = '\0';

			ps = psNumber + 1;
			size_t npIndex = 0;
			while ((size_t)*ps >= (size_t)'0' && (size_t)*ps <= (size_t)'9')
			{
				buf2[npIndex] = szNumber[(size_t)*ps - (size_t)'0'];
				npIndex++;
				ps++;
			}

			psBuf -= npIndex;
			memcpy(psBuf, buf2, npIndex * sizeof(wchar_t));
			psBuf--;
			*psBuf = L'点';
		}

		if (n64 == 0)
		{
			psBuf--;
			*psBuf = szNumber[0];
		}
		else
		{
			int npZeroType = 0;  // 0:还没有任何数字; 1:最近一个是零; 2:最近一个是数字
			int npIndex = 0, npMod;
			bool blpHaveUnit = false;

			while (n64 > 0)
			{
				npMod = (intptr_t)(n64 % 10);
				n64 /= 10;

				if (npIndex == 4 || npIndex == 8)
					blpHaveUnit = false;

				if (npMod == 0)
				{
					if (npZeroType == 2)
					{
						psBuf--;
						*psBuf = szNumber[0];
						npZeroType = 1;
					}
				}
				else
				{
					npZeroType = 2;

					if (npIndex > 0)
					{
						if (blpHaveUnit == false && npIndex >= 4)
						{
							if (npIndex < 8)
							{
								if (npIndex > 4)
								{
									psBuf--;
									*psBuf = szUnit[3];
								}

								blpHaveUnit = true;
							}
							else
							{
								if (npIndex > 8)
								{
									psBuf--;
									*psBuf = szUnit[7];
								}

								blpHaveUnit = true;
							}
						}

						psBuf--;
						*psBuf = szUnit[npIndex - 1];
					}

					psBuf--;
					*psBuf = szNumber[npMod];
				}

				npIndex++;
			}
		}

		if (blpNeg)
		{
			psBuf--;
			*psBuf = L'负';
		}
	}


	return psBuf;
}


KrnlnApi string 数值到大写A(double 欲转换形式的数值, bool 是否转换为简体) {
	return 宽文本到文本(数值到大写W(欲转换形式的数值, 是否转换为简体));
}
