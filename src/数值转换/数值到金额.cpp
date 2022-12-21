#include<string>
#include"文本转换.h"
using namespace std;


#define NERAZERO(db) (db >= -1e-6 && db <= 1e-6)
KrnlnApi wstring 数值到金额W(double 欲转换形式的数值, bool 是否转换为简体)
{
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

	if (NERAZERO(欲转换形式的数值))
	{
		*psBuf = szNumber[0];
		psBuf[1] = L'\0';
	}
	else if (欲转换形式的数值 > 9999999999999.0)
	{
		wcscpy_s(psBuf, 3, L"溢出");
	}
	else
	{
		psBuf = &buf[sizeof(buf) / sizeof(buf[0])];
		*psBuf = L'\0';

		欲转换形式的数值 *= 100;
		if (modf(欲转换形式的数值 + 1e-6, &欲转换形式的数值) >= 0.5)
			欲转换形式的数值++;
		long long n64 = (long long)欲转换形式的数值;

		if ((n64 % 10) == 0)
		{
			psBuf--;
			*psBuf = L'整';
		}

		int npZeroType = 0;  // 0:还没有任何数字; 1:最近一个是零; 2:最近一个是数字
		int npIndex = 0, npMod;
		bool blpHaveUnit = false, blpHaveYuan = false;

		while (n64 > 0)
		{
			npMod = n64 % 10;
			n64 /= 10;

			if (npIndex == 6 || npIndex == 10)
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

				if (npIndex < 2)
				{
					psBuf--;
					*psBuf = (npIndex == 0 ? L'分' : L'角');
				}
				else
				{
					if (blpHaveYuan == false)
					{
						psBuf--;
						*psBuf = L'元';
						blpHaveYuan = true;
					}

					if (blpHaveUnit == false && npIndex >= 6)
					{
						if (npIndex < 10)
						{
							if (npIndex > 6)
							{
								psBuf--;
								*psBuf = szUnit[3];
							}

							blpHaveUnit = true;
						}
						else
						{
							if (npIndex > 10)
							{
								psBuf--;
								*psBuf = szUnit[7];
							}

							blpHaveUnit = true;
						}
					}

					if (npIndex > 2)
					{
						psBuf--;
						*psBuf = szUnit[npIndex - 3];
					}
				}

				psBuf--;
				*psBuf = szNumber[npMod];
			}

			npIndex++;
		}

		if (blpNeg)
		{
			psBuf--;
			*psBuf = L'负';
		}
	}

	return psBuf;
}




KrnlnApi string 数值到金额A(double 欲转换形式的数值, bool 是否转换为简体) {

	return 宽文本到文本(数值到金额W(欲转换形式的数值, 是否转换为简体));

}










