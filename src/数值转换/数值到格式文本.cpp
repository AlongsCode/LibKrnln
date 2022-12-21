#include<string>

#pragma warning(disable:4996)
using namespace std;

#pragma region 宽字符辅助

#define NERAZERO(db) (db >= -1e-6 && db <= 1e-6)
static inline double RoundDouble(double db, const int npRound)
{
	if (NERAZERO(db))
		return db;

	const bool blpNegative = (db < 0);
	if (blpNegative)
		db = -db;

	if (npRound < 0)
	{
		double n = pow(10.0, (double)-npRound);
		db /= n;
		if (modf(db + 1e-6, &db) >= 0.5)
			db = db + 1;
		db *= n;
	}
	else if (npRound == 0)
	{
		if (modf(db + 1e-6, &db) >= 0.5)
			db = db + 1;
	}
	else
	{
		double n = pow(10.0, (double)npRound);
		db *= n;
		if (modf(db + 1e-6, &db) >= 0.5)
			db = db + 1;
		db /= n;
	}

	return (blpNegative ? -db : db);
}

#pragma endregion



KrnlnApi wstring 数值到格式文本W(double 欲转换为文本的数值, int 小数保留位数, bool 是否进行千分位分隔)
{
	if (小数保留位数 != INT_MAX)
		欲转换为文本的数值 = RoundDouble(欲转换为文本的数值, 小数保留位数);

	wchar_t buf[128] = { 0 };
	_swprintf(buf, L"%.15G", 欲转换为文本的数值);

	if (小数保留位数 != INT_MAX && 小数保留位数 > 0)
	{
		wchar_t* ps = wcschr(buf, '.');

		if (ps == NULL)
		{
			ps = &buf[wcslen(buf)];
			*ps++ = '.';
			for (int npIndex = 0; npIndex < 小数保留位数; npIndex++)
				*ps++ = '0';
			*ps = '\0';
		}
		else
		{
			ps++;

			int npFracNumber = 0;
			while (*ps != '\0')
			{
				npFracNumber++;
				ps++;
			}

			npFracNumber = 小数保留位数 - npFracNumber;
			if (npFracNumber > 0)
			{
				for (int npIndex = 0; npIndex < npFracNumber; npIndex++)
					*ps++ = '0';
				*ps = '\0';
			}
		}
	}

	if (是否进行千分位分隔)
	{
		wchar_t* psBegin = buf;
		if (*psBegin == '-')
			psBegin++;

		wchar_t* ps = psBegin;
		while (*ps != '\0')
		{
			const wchar_t ch = *ps++;
			if (ch != '.' && ((size_t)ch < (size_t)'0' || (size_t)ch >(size_t)'9'))
				break;
		}

		if (*ps == '\0')
		{
			wchar_t* psDot = wcschr(buf, '.');
			if (psDot == NULL)
				ps = buf + wcslen(buf);
			else
				ps = psDot;

			while (1)
			{
				ps -= 3;
				if (ps <= psBegin)
					break;
				memmove((void*)(ps + 1), ps, (wcslen(ps) + 1) * sizeof(wchar_t));
				*ps = ',';
			}
		}
	}

	return buf;
}



KrnlnApi string 数值到格式文本A(double 欲转换为文本的数值, int 小数保留位数, bool 是否进行千分位分隔) {

	char str[260] = { 0 };
	char strFomar[260] = { 0 };
	if (!欲转换为文本的数值)
	{
		strcpy(strFomar, "%lf");

	}
	else
	{
		int nNum = 小数保留位数;
		if (nNum < 0)
			nNum = 0;
		if (nNum > 8)
			nNum = 8;
		sprintf_s(&strFomar[1], 259, ".%dlf", nNum);
		strFomar[0] = '%';
	}

	sprintf_s(str, strFomar, 欲转换为文本的数值);

	if (是否进行千分位分隔)
	{
		strcpy_s(strFomar, str);
		char* pStr = strFomar;
		while (*pStr != 0 && *pStr != '.')
			pStr++;
		intptr_t nNum = pStr - strFomar;
		pStr = strFomar;
		if (strFomar[0] == '-')
		{
			nNum--;
			pStr++;
		}
		if (nNum > 3)
		{
			intptr_t nMax = nNum / 3;
			intptr_t nMod = nNum % 3;
			if (nMod)
				nMax++;
			intptr_t i = 0;
			char* pSrc = strFomar;
			char* pDest = str;

			while (i < nMax)
			{
				if (i == 0 && nMod)
					pStr += nMod;
				else
					pStr += 3;
				nNum = pStr - pSrc;

				if (i == nMax - 1)
				{
					strcat_s(pDest, sizeof(pSrc), pSrc);
					break;
				}
				strncpy_s(pDest, sizeof(pSrc), pSrc, nNum);
				pDest += nNum;
				*pDest = ',';
				pDest++;
				*pDest = 0;

				pSrc += nNum;
				pStr = pSrc;
				i++;

			}
		}
	}


	return str;

}




