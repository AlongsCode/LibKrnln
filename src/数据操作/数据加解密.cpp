#include <numeric>
#include<string>
#include<vector>


static unsigned long KnL[32] = { 0L };
static unsigned long KnR[32] = { 0L };
static unsigned long Kn3[32] = { 0L };
static unsigned char Df_Key[24] = {
	0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,
	0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,
	0x89,0xab,0xcd,0xef,0x01,0x23,0x45,0x67 };

static unsigned short bytebit[8] = {
	01, 02, 04, 010, 020, 040, 0100, 0200 };

static unsigned long bigbyte[24] = {
	0x800000L,	0x400000L,	0x200000L,	0x100000L,
	0x80000L,	0x40000L,	0x20000L,	0x10000L,
	0x8000L,	0x4000L,	0x2000L,	0x1000L,
	0x800L, 	0x400L, 	0x200L, 	0x100L,
	0x80L,		0x40L,		0x20L,		0x10L,
	0x8L,		0x4L,		0x2L,		0x1L };

/* Use the key schedule specified in the Standard (ANSI X3.92-1981). */

static unsigned char pc1[56] = {
	56, 48, 40, 32, 24, 16,  8,	 0, 57, 49, 41, 33, 25, 17,
	 9,  1, 58, 50, 42, 34, 26,	18, 10,  2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,	 6, 61, 53, 45, 37, 29, 21,
	13,  5, 60, 52, 44, 36, 28,	20, 12,  4, 27, 19, 11,  3 };

static unsigned char totrot[16] = {
	1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28 };

static unsigned char pc2[48] = {
	13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
	22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
	40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31 };





void cpkey(unsigned long* into)

{
	unsigned long* from, * endp;

	from = KnL, endp = &KnL[32];
	while (from < endp) *into++ = *from++;
	return;
}

void usekey(unsigned long* from)

{
	unsigned long* to, * endp;

	to = KnL, endp = &KnL[32];
	while (to < endp) *to++ = *from++;
	return;
}



static void scrunch(unsigned char* outof, unsigned long* into)
{
	*into = (*outof++ & 0xffL) << 24;
	*into |= (*outof++ & 0xffL) << 16;
	*into |= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into = (*outof++ & 0xffL) << 24;
	*into |= (*outof++ & 0xffL) << 16;
	*into |= (*outof++ & 0xffL) << 8;
	*into |= (*outof & 0xffL);
	return;
}

static void unscrun(unsigned long* outof, unsigned char* into)
{
	*into++ = (unsigned char)((*outof >> 24) & 0xffL);
	*into++ = (unsigned char)((*outof >> 16) & 0xffL);
	*into++ = (unsigned char)((*outof >> 8) & 0xffL);
	*into++ = (unsigned char)(*outof++ & 0xffL);
	*into++ = (unsigned char)((*outof >> 24) & 0xffL);
	*into++ = (unsigned char)((*outof >> 16) & 0xffL);
	*into++ = (unsigned char)((*outof >> 8) & 0xffL);
	*into = (unsigned char)(*outof & 0xffL);
	return;
}

static unsigned long SP1[64] = {
	0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
	0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
	0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
	0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
	0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
	0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
	0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
	0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
	0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
	0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
	0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
	0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
	0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
	0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L };

static unsigned long SP2[64] = {
	0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
	0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
	0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
	0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
	0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
	0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
	0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
	0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
	0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
	0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
	0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
	0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
	0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
	0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
	0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
	0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L };

static unsigned long SP3[64] = {
	0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
	0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
	0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
	0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
	0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
	0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
	0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
	0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
	0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
	0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
	0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
	0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
	0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
	0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
	0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
	0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L };

static unsigned long SP4[64] = {
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
	0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
	0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
	0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
	0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
	0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
	0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
	0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
	0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L };

static unsigned long SP5[64] = {
	0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
	0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
	0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
	0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
	0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
	0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
	0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
	0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
	0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
	0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
	0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
	0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
	0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
	0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
	0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
	0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L };

static unsigned long SP6[64] = {
	0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
	0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
	0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
	0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
	0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
	0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
	0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
	0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
	0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
	0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
	0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
	0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
	0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
	0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L };

static unsigned long SP7[64] = {
	0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
	0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
	0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
	0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
	0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
	0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
	0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
	0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
	0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
	0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
	0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
	0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
	0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
	0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
	0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
	0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L };

static unsigned long SP8[64] = {
	0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
	0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
	0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
	0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
	0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
	0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
	0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
	0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
	0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
	0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
	0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
	0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
	0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
	0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
	0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
	0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L };

static void desfunc(unsigned long* block, unsigned long* keys)
{
	unsigned long fval, work, right, leftt;
	int round;

	leftt = block[0];
	right = block[1];
	work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;
	right ^= work;
	leftt ^= (work << 4);
	work = ((leftt >> 16) ^ right) & 0x0000ffffL;
	right ^= work;
	leftt ^= (work << 16);
	work = ((right >> 2) ^ leftt) & 0x33333333L;
	leftt ^= work;
	right ^= (work << 2);
	work = ((right >> 8) ^ leftt) & 0x00ff00ffL;
	leftt ^= work;
	right ^= (work << 8);
	right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL;
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL;

	for (round = 0; round < 8; round++) {
		work = (right << 28) | (right >> 4);
		work ^= *keys++;
		fval = SP7[work & 0x3fL];
		fval |= SP5[(work >> 8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work = right ^ *keys++;
		fval |= SP8[work & 0x3fL];
		fval |= SP6[(work >> 8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		leftt ^= fval;
		work = (leftt << 28) | (leftt >> 4);
		work ^= *keys++;
		fval = SP7[work & 0x3fL];
		fval |= SP5[(work >> 8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work = leftt ^ *keys++;
		fval |= SP8[work & 0x3fL];
		fval |= SP6[(work >> 8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		right ^= fval;
	}

	right = (right << 31) | (right >> 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = (leftt << 31) | (leftt >> 1);
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);
	*block++ = right;
	*block = leftt;
	return;
}
static void cookey(unsigned long* raw1)
{
	unsigned long* cook, * raw0;
	unsigned long dough[32];
	int i;

	cook = dough;
	for (i = 0; i < 16; i++, raw1++) {
		raw0 = raw1++;
		*cook = (*raw0 & 0x00fc0000L) << 6;
		*cook |= (*raw0 & 0x00000fc0L) << 10;
		*cook |= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook = (*raw0 & 0x0003f000L) << 12;
		*cook |= (*raw0 & 0x0000003fL) << 16;
		*cook |= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
	}
	usekey(dough);
	return;
}
void deskey(unsigned char* key, int edf)
{
	int i, j, l, m, n;
	unsigned char pc1m[56], pcr[56];
	unsigned long kn[32];

	for (j = 0; j < 56; j++) {
		l = pc1[j];
		m = l & 07;
		pc1m[j] = (key[l >> 3] & bytebit[m]) ? 1 : 0;
	}
	for (i = 0; i < 16; i++) {
		if (edf == 1) m = (15 - i) << 1;
		else m = i << 1;
		n = m + 1;
		kn[m] = kn[n] = 0L;
		for (j = 0; j < 28; j++) {
			l = j + totrot[i];
			if (l < 28) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
		}
		for (j = 28; j < 56; j++) {
			l = j + totrot[i];
			if (l < 56) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
		}
		for (j = 0; j < 24; j++) {
			if (pcr[pc2[j]]) kn[m] |= bigbyte[j];
			if (pcr[pc2[j + 24]]) kn[n] |= bigbyte[j];
		}
	}
	cookey(kn);
	return;
}

void des(unsigned char* inblock, unsigned char* outblock)
{
	unsigned long work[2];

	scrunch(inblock, work);
	desfunc(work, KnL);
	unscrun(work, outblock);
	return;
}



void getKey(const std::string& szPassword, unsigned char key[8])
{
	unsigned char* pk = key;
	std::memset(pk, 0, sizeof(key));
	unsigned char* pe = pk + sizeof(key);
	for (const char& c : szPassword)
	{
		*pk++ ^= static_cast<unsigned char>(c);
		if (pk == pe)
		{
			pk = key;
		}
	}
}

/* !!! nDataSize 必须是 8 的整数倍 */
static void run(unsigned char* pd, int nDataSize, const std::string& szPassword, int blEncrypt)
{
	int nCount, i;
	unsigned char key[8];
	getKey(szPassword, key);

	if (blEncrypt)
		deskey(key, 0);
	else
		deskey(key, 1);

	nCount = nDataSize / 8;

	for (i = 0; i < nCount; i++)
	{
		des(pd, pd);
		pd += 8;
	}
}

// 结果将覆盖pd中的数据.
void encrypt(unsigned char* pd, int nDataSize, const std::string& szPassword)
{
	run(pd, nDataSize, szPassword, 1);
}

// 结果将覆盖pd中的数据.
void decrypt(unsigned char* pd, int nDataSize, const std::string& szPassword)
{
	run(pd, nDataSize, szPassword, 0);
}
typedef struct rc4_key
{
	unsigned char state[256];
	unsigned char x;
	unsigned char y;
} rc4_key;
static void swap_byte(unsigned char* a, unsigned char* b)
{
	unsigned char swapByte;

	swapByte = *a;
	*a = *b;
	*b = swapByte;
}

void prepare_key(const std::string& key_data, rc4_key* key)
{
	std::iota(std::begin(key->state), std::end(key->state), 0);  // Fill the state array with the integers from 0 to 255

	key->x = 0;
	key->y = 0;

	if (!key_data.empty())  // If the key data is not empty
	{
		size_t index1 = 0;
		unsigned char index2 = 0;
		for (size_t counter = 0; counter < 256; ++counter)
		{
			index2 = (key_data[index1] + key->state[counter] + index2) % 256;
			std::swap(key->state[counter], key->state[index2]);
			index1 = (index1 + 1) % key_data.size();
		}
	}
}


void rc4(unsigned char* buffer_ptr, size_t buffer_len, rc4_key* key)
{
	unsigned char x;
	unsigned char y;
	unsigned char* state;
	unsigned char xorIndex;
	size_t counter;

	x = key->x;
	y = key->y;

	state = &key->state[0];
	for (counter = 0; counter < buffer_len; counter++)
	{
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;
		swap_byte(&state[x], &state[y]);

		xorIndex = (state[x] + state[y]) % 256;
		buffer_ptr[counter] ^= state[xorIndex];
	}

	key->x = x;
	key->y = y;
}
inline void getKey(const std::wstring& password, unsigned char key[8])
{
	std::fill(key, key + 8, 0);  // Fill the key array with zeros
	auto pk = key;  // Iterator to the current position in the key array
	auto pe = key + 8;  // End iterator for the key array
	for (auto c : password)  // Iterate over characters in the password
	{
		*pk++ ^= static_cast<unsigned char>(c);  // XOR the character with the current key position
		if (pk == pe)  // If we have reached the end of the key array, reset the iterator to the beginning
			pk = key;
	}


}
inline void run(unsigned char* pd, size_t nDataSize, const  std::wstring& szPassword, int blEncrypt)
{

	unsigned char key[8];
	getKey(szPassword, key);

	if (blEncrypt)
		deskey(key, 0);
	else
		deskey(key, 1);

	size_t nCount = nDataSize / 8;

	for (size_t i = 0; i < nCount; i++)
	{
		des(pd, pd);
		pd += 8;
	}
}
inline void encrypt(unsigned char* pd, size_t nDataSize, const  std::wstring& szPassword)
{
	run(pd, nDataSize, szPassword, 1);
}
inline void decrypt(unsigned char* pd, size_t nDataSize, const  std::wstring& szPassword)
{
	run(pd, nDataSize, szPassword, 0);
}
inline void prepare_key(const std::wstring& key_data, rc4_key* key)
{
	std::iota(std::begin(key->state), std::end(key->state), 0);  // Fill the state array with the integers from 0 to 255

	key->x = 0;
	key->y = 0;

	if (!key_data.empty())  // If the key data is not empty
	{
		size_t index1 = 0;
		unsigned char index2 = 0;
		for (size_t counter = 0; counter < 256; ++counter)
		{
			index2 = (static_cast<unsigned char>(key_data[index1]) + key->state[counter] + index2) % 256;
			std::swap(key->state[counter], key->state[index2]);
			index1 = (index1 + 1) % key_data.size();
		}
	}
}

std::vector<unsigned char> RunEncrypt(std::vector<unsigned char> data, const std::string& password, const int algorithm, const bool isEncrypt)
{
	unsigned char* input = data.data();
	int inputSize = static_cast<int>(data.size());
	int mode = (algorithm == 2) ? 2 : 1;

	unsigned char* output = nullptr;
	unsigned char* pnew = nullptr;
	int outputSize = 0;

	if (inputSize > 0)
	{
		if (mode == 1)
		{
			if (isEncrypt)
			{
				int padding = (inputSize + sizeof(int)) % 8;
				if (padding > 0)
				{
					padding = 8 - padding;
				}
				outputSize = sizeof(int) + inputSize + padding;
				pnew = output = new unsigned char[outputSize];
				if (output != nullptr)
				{
					std::memset(output, 0, outputSize);
					*reinterpret_cast<int*>(output) = inputSize;
					std::memcpy(output + sizeof(int), input, inputSize);
					encrypt(output, outputSize, password);
				}
				else
				{
					outputSize = 0;
				}
			}
			else if ((inputSize % 8) == 0)
			{


				pnew = output = new unsigned char[inputSize];
				if (output != nullptr)
				{
					std::memcpy(output, input, inputSize);
					decrypt(output, inputSize, password);
					outputSize = *(int*)(output);
					if (outputSize <= 0 || inputSize >= outputSize + 12 || outputSize > inputSize - 4)
					{
						outputSize = 0;
					}
					else
					{

						output += sizeof(int);
					}

				}
			}
		}
		else
		{
			rc4_key key;
			prepare_key(password, &key);
			pnew = output = new unsigned char[inputSize];
			if (output != nullptr)
			{
				std::memcpy(output, input, inputSize);
				outputSize = inputSize;
				rc4(output, outputSize, &key);
			}
		}
	}
	std::vector<unsigned char> result;
	if (pnew)
	{
		result = std::vector<unsigned char>(output, output + outputSize);
		delete[] pnew;
	}

	return result;
}


std::vector<unsigned char> RunEncrypt(std::vector<unsigned char> data, const std::wstring& password, const int algorithm, const bool isEncrypt)
{
	unsigned char* input = data.data();
	int inputSize = static_cast<int>(data.size());
	int mode = (algorithm == 2) ? 2 : 1;

	unsigned char* output = nullptr;
	unsigned char* pnew = nullptr;
	int outputSize = 0;

	if (inputSize > 0)
	{
		if (mode == 1)
		{
			if (isEncrypt)
			{
				int padding = (inputSize + sizeof(int)) % 8;
				if (padding > 0)
				{
					padding = 8 - padding;
				}
				outputSize = sizeof(int) + inputSize + padding;
				pnew = output = new unsigned char[outputSize];
				if (output != nullptr)
				{
					std::memset(output, 0, outputSize);
					*reinterpret_cast<int*>(output) = inputSize;
					std::memcpy(output + sizeof(int), input, inputSize);
					encrypt(output, outputSize, password);
				}
				else
				{
					outputSize = 0;
				}
			}
			else if ((inputSize % 8) == 0)
			{


				pnew = output = new unsigned char[inputSize];
				if (output != nullptr)
				{
					std::memcpy(output, input, inputSize);
					decrypt(output, inputSize, password);
					outputSize = *(int*)(output);
					if (outputSize <= 0 || inputSize >= outputSize + 12 || outputSize > inputSize - 4)
					{
						outputSize = 0;
					}
					else
					{

						output += sizeof(int);
					}

				}
			}
		}
		else
		{
			rc4_key key;
			prepare_key(password, &key);
			pnew = output = new unsigned char[inputSize];
			if (output != nullptr)
			{
				std::memcpy(output, input, inputSize);
				outputSize = inputSize;
				rc4(output, outputSize, &key);
			}
		}
	}
	std::vector<unsigned char> result;
	if (pnew)
	{
		result = std::vector<unsigned char>(output, output + outputSize);
		delete[] pnew;
	}

	return result;
}

KrnlnApi std::vector<unsigned char> 加密数据(std::vector<unsigned char> 字节集数据, const std::string& 密码文本, const int 加密算法)
{
	return RunEncrypt(字节集数据, 密码文本, 加密算法, 1);
}
KrnlnApi std::vector<unsigned char> 加密数据(std::vector<unsigned char> 字节集数据, const std::wstring& 密码文本, const int  加密算法)
{
	return RunEncrypt(字节集数据, 密码文本, 加密算法, 1);
}
KrnlnApi std::vector<unsigned char> 解密数据(std::vector<unsigned char> 字节集数据, const std::wstring& 密码文本, int 加密算法)
{
	return RunEncrypt(字节集数据, 密码文本, 加密算法, 0);
}
KrnlnApi std::vector<unsigned char> 解密数据(std::vector<unsigned char> 字节集数据, const std::string& 密码文本, int  加密算法)
{
	return RunEncrypt(字节集数据, 密码文本, 加密算法, 0);
}
