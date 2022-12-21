#include<vector>
#include<string>

//MD5ChecksumDefines.h : MD5 Checksum constants

//Magic initialization constants
#define MD5_INIT_STATE_0 0x67452301
#define MD5_INIT_STATE_1 0xefcdab89
#define MD5_INIT_STATE_2 0x98badcfe
#define MD5_INIT_STATE_3 0x10325476

//Constants for Transform routine.
#define MD5_S11  7
#define MD5_S12 12
#define MD5_S13 17
#define MD5_S14 22
#define MD5_S21  5
#define MD5_S22  9
#define MD5_S23 14
#define MD5_S24 20
#define MD5_S31  4
#define MD5_S32 11
#define MD5_S33 16
#define MD5_S34 23
#define MD5_S41  6
#define MD5_S42 10
#define MD5_S43 15
#define MD5_S44 21

//Transformation Constants - Round 1
#define MD5_T01  0xd76aa478 //Transformation Constant 1 
#define MD5_T02  0xe8c7b756 //Transformation Constant 2
#define MD5_T03  0x242070db //Transformation Constant 3
#define MD5_T04  0xc1bdceee //Transformation Constant 4
#define MD5_T05  0xf57c0faf //Transformation Constant 5
#define MD5_T06  0x4787c62a //Transformation Constant 6
#define MD5_T07  0xa8304613 //Transformation Constant 7
#define MD5_T08  0xfd469501 //Transformation Constant 8
#define MD5_T09  0x698098d8 //Transformation Constant 9
#define MD5_T10  0x8b44f7af //Transformation Constant 10
#define MD5_T11  0xffff5bb1 //Transformation Constant 11
#define MD5_T12  0x895cd7be //Transformation Constant 12
#define MD5_T13  0x6b901122 //Transformation Constant 13
#define MD5_T14  0xfd987193 //Transformation Constant 14
#define MD5_T15  0xa679438e //Transformation Constant 15
#define MD5_T16  0x49b40821 //Transformation Constant 16

//Transformation Constants - Round 2
#define MD5_T17  0xf61e2562 //Transformation Constant 17
#define MD5_T18  0xc040b340 //Transformation Constant 18
#define MD5_T19  0x265e5a51 //Transformation Constant 19
#define MD5_T20  0xe9b6c7aa //Transformation Constant 20
#define MD5_T21  0xd62f105d //Transformation Constant 21
#define MD5_T22  0x02441453 //Transformation Constant 22
#define MD5_T23  0xd8a1e681 //Transformation Constant 23
#define MD5_T24  0xe7d3fbc8 //Transformation Constant 24
#define MD5_T25  0x21e1cde6 //Transformation Constant 25
#define MD5_T26  0xc33707d6 //Transformation Constant 26
#define MD5_T27  0xf4d50d87 //Transformation Constant 27
#define MD5_T28  0x455a14ed //Transformation Constant 28
#define MD5_T29  0xa9e3e905 //Transformation Constant 29
#define MD5_T30  0xfcefa3f8 //Transformation Constant 30
#define MD5_T31  0x676f02d9 //Transformation Constant 31
#define MD5_T32  0x8d2a4c8a //Transformation Constant 32

//Transformation Constants - Round 3
#define MD5_T33  0xfffa3942 //Transformation Constant 33
#define MD5_T34  0x8771f681 //Transformation Constant 34
#define MD5_T35  0x6d9d6122 //Transformation Constant 35
#define MD5_T36  0xfde5380c //Transformation Constant 36
#define MD5_T37  0xa4beea44 //Transformation Constant 37
#define MD5_T38  0x4bdecfa9 //Transformation Constant 38
#define MD5_T39  0xf6bb4b60 //Transformation Constant 39
#define MD5_T40  0xbebfbc70 //Transformation Constant 40
#define MD5_T41  0x289b7ec6 //Transformation Constant 41
#define MD5_T42  0xeaa127fa //Transformation Constant 42
#define MD5_T43  0xd4ef3085 //Transformation Constant 43
#define MD5_T44  0x04881d05 //Transformation Constant 44
#define MD5_T45  0xd9d4d039 //Transformation Constant 45
#define MD5_T46  0xe6db99e5 //Transformation Constant 46
#define MD5_T47  0x1fa27cf8 //Transformation Constant 47
#define MD5_T48  0xc4ac5665 //Transformation Constant 48

//Transformation Constants - Round 4
#define MD5_T49  0xf4292244 //Transformation Constant 49
#define MD5_T50  0x432aff97 //Transformation Constant 50
#define MD5_T51  0xab9423a7 //Transformation Constant 51
#define MD5_T52  0xfc93a039 //Transformation Constant 52
#define MD5_T53  0x655b59c3 //Transformation Constant 53
#define MD5_T54  0x8f0ccc92 //Transformation Constant 54
#define MD5_T55  0xffeff47d //Transformation Constant 55
#define MD5_T56  0x85845dd1 //Transformation Constant 56
#define MD5_T57  0x6fa87e4f //Transformation Constant 57
#define MD5_T58  0xfe2ce6e0 //Transformation Constant 58
#define MD5_T59  0xa3014314 //Transformation Constant 59
#define MD5_T60  0x4e0811a1 //Transformation Constant 60
#define MD5_T61  0xf7537e82 //Transformation Constant 61
#define MD5_T62  0xbd3af235 //Transformation Constant 62
#define MD5_T63  0x2ad7d2bb //Transformation Constant 63
#define MD5_T64  0xeb86d391 //Transformation Constant 64


//Null data (except for first unsigned char) used to finalise the checksum calculation
static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


class CMD5Checksum
{
public:
	//constructor/destructor
	CMD5Checksum();
	virtual ~CMD5Checksum() {};

	//RSA MD5 implementation
	void Transform(unsigned char Block[64]);
	void Update(unsigned char* Input, unsigned int nInputLen);
	std::string Final();
	std::wstring FinalW();
	inline unsigned int RotateLeft(unsigned int x, int n);
	inline void FF(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline void GG(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline void HH(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);
	inline void II(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T);

	//utility functions
	void DWordToByte(unsigned char* Output, unsigned int* Input, unsigned int nLength);
	void ByteToDWord(unsigned int* Output, unsigned char* Input, unsigned int nLength);

private:
	unsigned char  m_lpszBuffer[64];		//input buffer
	unsigned int m_nCount[2];			//number of bits, modulo 2^64 (lsb first)
	unsigned int m_lMD5[4];			//MD5 checksum
};



unsigned int CMD5Checksum::RotateLeft(unsigned int x, int n)
{
	//rotate and return x
	return (x << n) | (x >> (32 - n));
}


void CMD5Checksum::FF(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T)
{
	unsigned int F = (B & C) | (~B & D);
	A += F + X + T;
	A = RotateLeft(A, S);
	A += B;
}



void CMD5Checksum::GG(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T)
{
	unsigned int G = (B & D) | (C & ~D);
	A += G + X + T;
	A = RotateLeft(A, S);
	A += B;
}


void CMD5Checksum::HH(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T)
{
	unsigned int H = (B ^ C ^ D);
	A += H + X + T;
	A = RotateLeft(A, S);
	A += B;
}


/*****************************************************************************************
FUNCTION:		CMD5Checksum::II
DETAILS:		protected
DESCRIPTION:	Implementation of basic MD5 transformation algorithm
RETURNS:		none
ARGUMENTS:		unsigned int &A, B, C, D : Current (partial) checksum
				unsigned int X           : Input data
				unsigned int S			  : MD5_SXX Transformation constant
				unsigned int T			  :	MD5_TXX Transformation constant
NOTES:			None
*****************************************************************************************/
void CMD5Checksum::II(unsigned int& A, unsigned int B, unsigned int C, unsigned int D, unsigned int X, unsigned int S, unsigned int T)
{
	unsigned int I = (C ^ (B | ~D));
	A += I + X + T;
	A = RotateLeft(A, S);
	A += B;
}


/*****************************************************************************************
FUNCTION:		CMD5Checksum::ByteToDWord
DETAILS:		private
DESCRIPTION:	Transfers the data in an 8 bit array to a 32 bit array
RETURNS:		void
ARGUMENTS:		unsigned int* Output : the 32 bit (unsigned int) destination array
				unsigned char* Input	  : the 8 bit (unsigned char) source array
				unsigned int nLength  : the number of 8 bit data items in the source array
NOTES:			Four unsigned charS from the input array are transferred to each unsigned int entry
				of the output array. The first unsigned char is transferred to the bits (0-7)
				of the output unsigned int, the second unsigned char to bits 8-15 etc.
				The algorithm assumes that the input array is a multiple of 4 bytes long
				so that there is a perfect fit into the array of 32 bit words.
*****************************************************************************************/
void CMD5Checksum::ByteToDWord(unsigned int* Output, unsigned char* Input, unsigned int nLength)
{
	//entry invariants
	//ASSERT( nLength % 4 == 0 );
	//ASSERT( AfxIsValidAddress(Output, nLength/4, TRUE) );
	//ASSERT( AfxIsValidAddress(Input, nLength, FALSE) );

	//initialisations
	unsigned int i = 0;	//index to Output array
	unsigned int j = 0;	//index to Input array

	//transfer the data by shifting and copying
	for (; j < nLength; i++, j += 4)
	{
		Output[i] = (unsigned int)Input[j] |
			(unsigned int)Input[j + 1] << 8 |
			(unsigned int)Input[j + 2] << 16 |
			(unsigned int)Input[j + 3] << 24;
	}
}

/*****************************************************************************************
FUNCTION:		CMD5Checksum::Transform
DETAILS:		protected
DESCRIPTION:	MD5 basic transformation algorithm;  transforms 'm_lMD5'
RETURNS:		void
ARGUMENTS:		unsigned char Block[64]
NOTES:			An MD5 checksum is calculated by four rounds of 'Transformation'.
				The MD5 checksum currently held in m_lMD5 is merged by the
				transformation process with data passed in 'Block'.
*****************************************************************************************/
void CMD5Checksum::Transform(unsigned char Block[64])
{
	//initialise local data with current checksum
	unsigned int a = m_lMD5[0];
	unsigned int b = m_lMD5[1];
	unsigned int c = m_lMD5[2];
	unsigned int d = m_lMD5[3];

	//copy unsigned charS from input 'Block' to an array of unsigned intS 'X'
	unsigned int X[16];
	ByteToDWord(X, Block, 64);

	//Perform Round 1 of the transformation
	FF(a, b, c, d, X[0], MD5_S11, MD5_T01);
	FF(d, a, b, c, X[1], MD5_S12, MD5_T02);
	FF(c, d, a, b, X[2], MD5_S13, MD5_T03);
	FF(b, c, d, a, X[3], MD5_S14, MD5_T04);
	FF(a, b, c, d, X[4], MD5_S11, MD5_T05);
	FF(d, a, b, c, X[5], MD5_S12, MD5_T06);
	FF(c, d, a, b, X[6], MD5_S13, MD5_T07);
	FF(b, c, d, a, X[7], MD5_S14, MD5_T08);
	FF(a, b, c, d, X[8], MD5_S11, MD5_T09);
	FF(d, a, b, c, X[9], MD5_S12, MD5_T10);
	FF(c, d, a, b, X[10], MD5_S13, MD5_T11);
	FF(b, c, d, a, X[11], MD5_S14, MD5_T12);
	FF(a, b, c, d, X[12], MD5_S11, MD5_T13);
	FF(d, a, b, c, X[13], MD5_S12, MD5_T14);
	FF(c, d, a, b, X[14], MD5_S13, MD5_T15);
	FF(b, c, d, a, X[15], MD5_S14, MD5_T16);

	//Perform Round 2 of the transformation
	GG(a, b, c, d, X[1], MD5_S21, MD5_T17);
	GG(d, a, b, c, X[6], MD5_S22, MD5_T18);
	GG(c, d, a, b, X[11], MD5_S23, MD5_T19);
	GG(b, c, d, a, X[0], MD5_S24, MD5_T20);
	GG(a, b, c, d, X[5], MD5_S21, MD5_T21);
	GG(d, a, b, c, X[10], MD5_S22, MD5_T22);
	GG(c, d, a, b, X[15], MD5_S23, MD5_T23);
	GG(b, c, d, a, X[4], MD5_S24, MD5_T24);
	GG(a, b, c, d, X[9], MD5_S21, MD5_T25);
	GG(d, a, b, c, X[14], MD5_S22, MD5_T26);
	GG(c, d, a, b, X[3], MD5_S23, MD5_T27);
	GG(b, c, d, a, X[8], MD5_S24, MD5_T28);
	GG(a, b, c, d, X[13], MD5_S21, MD5_T29);
	GG(d, a, b, c, X[2], MD5_S22, MD5_T30);
	GG(c, d, a, b, X[7], MD5_S23, MD5_T31);
	GG(b, c, d, a, X[12], MD5_S24, MD5_T32);

	//Perform Round 3 of the transformation
	HH(a, b, c, d, X[5], MD5_S31, MD5_T33);
	HH(d, a, b, c, X[8], MD5_S32, MD5_T34);
	HH(c, d, a, b, X[11], MD5_S33, MD5_T35);
	HH(b, c, d, a, X[14], MD5_S34, MD5_T36);
	HH(a, b, c, d, X[1], MD5_S31, MD5_T37);
	HH(d, a, b, c, X[4], MD5_S32, MD5_T38);
	HH(c, d, a, b, X[7], MD5_S33, MD5_T39);
	HH(b, c, d, a, X[10], MD5_S34, MD5_T40);
	HH(a, b, c, d, X[13], MD5_S31, MD5_T41);
	HH(d, a, b, c, X[0], MD5_S32, MD5_T42);
	HH(c, d, a, b, X[3], MD5_S33, MD5_T43);
	HH(b, c, d, a, X[6], MD5_S34, MD5_T44);
	HH(a, b, c, d, X[9], MD5_S31, MD5_T45);
	HH(d, a, b, c, X[12], MD5_S32, MD5_T46);
	HH(c, d, a, b, X[15], MD5_S33, MD5_T47);
	HH(b, c, d, a, X[2], MD5_S34, MD5_T48);

	//Perform Round 4 of the transformation
	II(a, b, c, d, X[0], MD5_S41, MD5_T49);
	II(d, a, b, c, X[7], MD5_S42, MD5_T50);
	II(c, d, a, b, X[14], MD5_S43, MD5_T51);
	II(b, c, d, a, X[5], MD5_S44, MD5_T52);
	II(a, b, c, d, X[12], MD5_S41, MD5_T53);
	II(d, a, b, c, X[3], MD5_S42, MD5_T54);
	II(c, d, a, b, X[10], MD5_S43, MD5_T55);
	II(b, c, d, a, X[1], MD5_S44, MD5_T56);
	II(a, b, c, d, X[8], MD5_S41, MD5_T57);
	II(d, a, b, c, X[15], MD5_S42, MD5_T58);
	II(c, d, a, b, X[6], MD5_S43, MD5_T59);
	II(b, c, d, a, X[13], MD5_S44, MD5_T60);
	II(a, b, c, d, X[4], MD5_S41, MD5_T61);
	II(d, a, b, c, X[11], MD5_S42, MD5_T62);
	II(c, d, a, b, X[2], MD5_S43, MD5_T63);
	II(b, c, d, a, X[9], MD5_S44, MD5_T64);

	//add the transformed values to the current checksum
	m_lMD5[0] += a;
	m_lMD5[1] += b;
	m_lMD5[2] += c;
	m_lMD5[3] += d;
}


/*****************************************************************************************
CONSTRUCTOR:	CMD5Checksum
DESCRIPTION:	Initialises member data
ARGUMENTS:		None
NOTES:			None
*****************************************************************************************/
CMD5Checksum::CMD5Checksum()
{
	// zero members
	memset(m_lpszBuffer, 0, 64);
	m_nCount[0] = m_nCount[1] = 0;

	// Load magic state initialization constants
	m_lMD5[0] = MD5_INIT_STATE_0;
	m_lMD5[1] = MD5_INIT_STATE_1;
	m_lMD5[2] = MD5_INIT_STATE_2;
	m_lMD5[3] = MD5_INIT_STATE_3;
}

/*****************************************************************************************
FUNCTION:		CMD5Checksum::DWordToByte
DETAILS:		private
DESCRIPTION:	Transfers the data in an 32 bit array to a 8 bit array
RETURNS:		void
ARGUMENTS:		unsigned char* Output  : the 8 bit destination array
				unsigned int* Input  : the 32 bit source array
				unsigned int nLength  : the number of 8 bit data items in the source array
NOTES:			One unsigned int from the input array is transferred into four unsigned charS
				in the output array. The first (0-7) bits of the first unsigned int are
				transferred to the first output unsigned char, bits bits 8-15 are transferred from
				the second unsigned char etc.

				The algorithm assumes that the output array is a multiple of 4 bytes long
				so that there is a perfect fit of 8 bit unsigned charS into the 32 bit unsigned ints.
*****************************************************************************************/
void CMD5Checksum::DWordToByte(unsigned char* Output, unsigned int* Input, unsigned int nLength)
{

	unsigned int i = 0;
	unsigned int j = 0;
	for (; j < nLength; i++, j += 4)
	{
		Output[j] = (unsigned char)(Input[i] & 0xff);
		Output[j + 1] = (unsigned char)((Input[i] >> 8) & 0xff);
		Output[j + 2] = (unsigned char)((Input[i] >> 16) & 0xff);
		Output[j + 3] = (unsigned char)((Input[i] >> 24) & 0xff);
	}
}

std::string CMD5Checksum::Final()
{
	// Save number of bits
	unsigned char Bits[8];
	DWordToByte(Bits, m_nCount, 8);

	// Pad out to 56 mod 64.
	unsigned int nIndex = (unsigned int)((m_nCount[0] >> 3) & 0x3f);
	unsigned int nPadLen = (nIndex < 56) ? (56 - nIndex) : (120 - nIndex);
	Update(PADDING, nPadLen);

	// Append length (before padding)
	Update(Bits, 8);

	// Store final state in 'lpszMD5'
	const int nMD5Size = 16;
	unsigned char lpszMD5[nMD5Size];
	DWordToByte(lpszMD5, m_lMD5, nMD5Size);

	std::string result;
	result.reserve(32);  // Pre-allocate space for 32 characters in the string
	char buf[10];
	for (int i = 0; i < nMD5Size; i++)
	{
		if (lpszMD5[i] == 0) {
			result += "00";
		}
		else if (lpszMD5[i] <= 15) {
			sprintf_s(buf, "0%x", lpszMD5[i]);
			result += buf;
		}
		else {
			sprintf_s(buf, "%x", lpszMD5[i]);
			result += buf;
		}
	}

	return result;
}
std::wstring CMD5Checksum::FinalW()
{
	// Save number of bits
	unsigned char Bits[8];
	DWordToByte(Bits, m_nCount, 8);

	// Pad out to 56 mod 64.
	unsigned int nIndex = (unsigned int)((m_nCount[0] >> 3) & 0x3f);
	unsigned int nPadLen = (nIndex < 56) ? (56 - nIndex) : (120 - nIndex);
	Update(PADDING, nPadLen);

	// Append length (before padding)
	Update(Bits, 8);

	// Store final state in 'lpszMD5'
	const int nMD5Size = 16;
	unsigned char lpszMD5[nMD5Size];
	DWordToByte(lpszMD5, m_lMD5, nMD5Size);

	std::wstring result;
	result.reserve(32);  // Pre-allocate space for 32 characters in the string
	wchar_t buf[10];
	for (int i = 0; i < nMD5Size; i++)
	{
		if (lpszMD5[i] == 0) {
			result += L"00";
		}
		else if (lpszMD5[i] <= 15) {
			swprintf_s(buf, L"0%x", lpszMD5[i]);
			result += buf;
		}
		else {
			swprintf_s(buf, L"%x", lpszMD5[i]);
			result += buf;
		}
	}

	return result;
}

void CMD5Checksum::Update(unsigned char* Input, unsigned int nInputLen)
{
	//Compute number of bytes mod 64
	unsigned int nIndex = (unsigned int)((m_nCount[0] >> 3) & 0x3F);

	//Update number of bits
	if ((m_nCount[0] += nInputLen << 3) < (nInputLen << 3))
	{
		m_nCount[1]++;
	}
	m_nCount[1] += (nInputLen >> 29);

	//Transform as many times as possible.
	unsigned int i = 0;
	unsigned int nPartLen = 64 - nIndex;
	if (nInputLen >= nPartLen)
	{
		memcpy(&m_lpszBuffer[nIndex], Input, nPartLen);
		Transform(m_lpszBuffer);
		for (i = nPartLen; i + 63 < nInputLen; i += 64)
		{
			Transform(&Input[i]);
		}
		nIndex = 0;
	}
	else
	{
		i = 0;
	}

	// Buffer remaining input
	memcpy(&m_lpszBuffer[nIndex], &Input[i], nInputLen - i);
}






KrnlnApi std::string 取数据摘要A(std::vector<unsigned char> WannaData)
{

	CMD5Checksum MD5Checksum;
	MD5Checksum.Update(WannaData.data(), (unsigned int)WannaData.size());
	return MD5Checksum.Final();
}
KrnlnApi std::wstring 取数据摘要W(std::vector<unsigned char> WannaData)
{

	CMD5Checksum MD5Checksum;
	MD5Checksum.Update(WannaData.data(), (unsigned int)WannaData.size());
	return MD5Checksum.FinalW();
}