#pragma once
/*�Ƚ���Ҫ��ƽ̨�ض�������Ȼ���ں��Ŀ�֮��*/
#ifdef _WIN32
/*���ļ���Դ����������ʾ��ѡ��ָ���ļ�,�༭ģʽΪ����ѡ��ʱ��Ϊ������ģʽ*/
bool ��λ�ļ�(const std::wstring& �ļ�·��, bool �༭ģʽ = false);
bool ��λ�ļ�(const std::string& �ļ�·��, bool �༭ģʽ = false);

long long ȡ����ʣ��ռ�(char �����������ַ�);
long long ȡ����ʣ��ռ�(wchar_t �����������ַ�);
long long ȡ����ʣ��ռ�(const wstring& �����������ַ� = L"");
long long ȡ����ʣ��ռ�(const string& �����������ַ�);

bool �ô��̾��(const string& �����������ַ�, const string& ������ľ���ı� = "");
bool �ô��̾��(const wstring& �����������ַ� = L"", const wstring& ������ľ���ı� = L"");
bool �ô��̾��(char �����������ַ�, const string& ������ľ���ı� = "");
bool �ô��̾��(wchar_t �����������ַ�, const wstring& ������ľ���ı� = L"");

string ȡ���̾��A(char �����������ַ�);
wstring ȡ���̾��W(wchar_t �����������ַ�);
string ȡ���̾��A(const string& �����������ַ� = "");
wstring ȡ���̾��W(const wstring& �����������ַ� = L"");


long long ȡ�����ܿռ�(wchar_t �����������ַ�);
long long ȡ�����ܿռ�(char �����������ַ�);
long long ȡ�����ܿռ�(const wstring& �����������ַ� = L"");
long long ȡ�����ܿռ�(const string& �����������ַ�);

/*���̲��� - ���ļ�����
	���ø�ʽ�� ���߼��͡� ���ļ����� ���ı��� �����������Ե��ļ����ƣ������� ������Ϊ������ֵ�� - ϵͳ����֧�ֿ�->���̲���
	Ӣ�����ƣ�SetAttr
	Ϊһ���ļ�����������Ϣ���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
	����<1>������Ϊ�������������Ե��ļ����ơ�������Ϊ���ı��ͣ�text������
	����<2>������Ϊ��������Ϊ������ֵ��������Ϊ�������ͣ�int����������ֵ����Ϊ���³���ֵ����ͣ� 1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 32��#�浵�ļ� ��ͨ������Щ����ֵ����������һ�����ö���ļ����ԡ�
*/
bool ���ļ�����(const wstring& �����������Ե��ļ�����, int ������Ϊ������ֵ);
/*���̲��� - ���ļ�����
	���ø�ʽ�� ���߼��͡� ���ļ����� ���ı��� �����������Ե��ļ����ƣ������� ������Ϊ������ֵ�� - ϵͳ����֧�ֿ�->���̲���
	Ӣ�����ƣ�SetAttr
	Ϊһ���ļ�����������Ϣ���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
	����<1>������Ϊ�������������Ե��ļ����ơ�������Ϊ���ı��ͣ�text������
	����<2>������Ϊ��������Ϊ������ֵ��������Ϊ�������ͣ�int����������ֵ����Ϊ���³���ֵ����ͣ� 1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 32��#�浵�ļ� ��ͨ������Щ����ֵ����������һ�����ö���ļ����ԡ�
*/
bool ���ļ�����(const string& �����������Ե��ļ�����, int ������Ϊ������ֵ);
#pragma region ȡ���̾��

#ifdef _UNICODE
#define ȡ���̾��() ȡ���̾��A()
#else
#define ȡ���̾��() ȡ���̾��W()
#endif

#else
#endif



/*ȫƽ̨ͨ�ú���*/
bool �ı�������(const string& ���ı䵽��������);
bool �ı�������(const wstring& ���ı䵽��������);
bool �ı�������(char ���ı䵽��������);
bool �ı�������(wchar_t ���ı䵽��������);

bool �ı�Ŀ¼(const string& ���ı䵽��Ŀ¼);
bool �ı�Ŀ¼(const wstring& ���ı䵽��Ŀ¼);

/*ǿ�ƴ����Ὣ�����ڸ�Ŀ¼��Ŀ¼�д����ļ�*/
bool ����Ŀ¼(const string& ��������Ŀ¼����, bool ǿ�ƴ��� = false);
/*ǿ�ƴ����Ὣ�����ڸ�Ŀ¼��Ŀ¼�д����ļ�*/
bool ����Ŀ¼(const wstring& ��������Ŀ¼����, bool ǿ�ƴ��� = false);


bool ɾ��Ŀ¼(const string& ��ɾ����Ŀ¼����);
bool ɾ��Ŀ¼(const wstring& ��ɾ����Ŀ¼����);

bool �����ļ�(const string& �����Ƶ��ļ���, const string& ���Ƶ����ļ���);
bool �����ļ�(const wstring& �����Ƶ��ļ���, const wstring& ���Ƶ����ļ���);

bool �ƶ��ļ�(const wstring& ���ƶ����ļ�, const wstring& �ƶ�����λ��);
bool �ƶ��ļ�(const string& ���ƶ����ļ�, const string& �ƶ�����λ��);

bool ɾ���ļ�(const wstring& ��ɾ�����ļ���);
bool ɾ���ļ�(const string& ��ɾ�����ļ���);

bool �ļ�����(const wstring& ��������ԭ�ļ���Ŀ¼��, const wstring& ������Ϊ�����ļ���Ŀ¼��);
bool �ļ�����(const string& ��������ԭ�ļ���Ŀ¼��, const string& ������Ϊ�����ļ���Ŀ¼��);

bool �ļ��Ƿ����(const string& �����Ե��ļ�����);
bool �ļ��Ƿ����(const wstring& �����Ե��ļ�����);
//�������������Ѱ���ļ�����һ���������������ڵ��ڴ棬�벻��ʱ��ʱ�ͷ�;
string Ѱ���ļ�(string ��Ѱ�ҵ��ļ���Ŀ¼���� = "", int ��Ѱ���ļ������� = 0);
wstring Ѱ���ļ�(const wstring& ��Ѱ�ҵ��ļ���Ŀ¼���� = L"", int ��Ѱ���ļ������� = 0);

std::tm ȡ�ļ�ʱ��(const string& �ļ���);
std::tm ȡ�ļ�ʱ��(const wstring& �ļ���);

int ȡ�ļ�����(const string& �ļ���);
int ȡ�ļ�����(const wstring& �ļ���);

long long ȡ�ļ��ߴ�(const wstring& �ļ���);
long long ȡ�ļ��ߴ�(const string& �ļ���);
#define ȡ�ļ���С(�ļ���) ȡ�ļ��ߴ�(�ļ���);




//Ĭ���������Ŀ¼�����Ϳ���ָ��Ϊ�����ļ����ͣ���"txt"
bool ���Ŀ¼(const std::string& Ҫɾ���ļ���Ŀ¼, const std::string& �ļ����� = "", bool ɾ���ļ��� = true);
//Ĭ���������Ŀ¼�����Ϳ���ָ��Ϊ�����ļ����ͣ���"txt"
bool ���Ŀ¼(const std::wstring& Ҫɾ���ļ���Ŀ¼, const std::wstring& �ļ����� = L"", bool ɾ���ļ��� = true);
string ȡ��ʱ�ļ���A(const string& Ŀ¼�� = "");
wstring ȡ��ʱ�ļ���W(const wstring& Ŀ¼�� = L"");
#pragma region ȡ��ʱ�ļ���
std::string ȡ��·��(const std::string& ��ȡ��·����Ŀ¼���ļ�);
std::wstring ȡ��·��(const std::wstring& ��ȡ��·����Ŀ¼���ļ�);
#ifdef _UNICODE
#define ȡ��ʱ�ļ���() ȡ��ʱ�ļ���A()
#else
#define ȡ��ʱ�ļ���() ȡ��ʱ�ļ���W()
#endif

#pragma endregion

vector<unsigned char> �����ļ�(const string& �ļ���);
vector<unsigned char> �����ļ�(const wstring& �ļ���);


bool д���ļ�(const string& �ļ���, vector<unsigned char>  ��д���ļ�������);
bool д���ļ�(const wstring& �ļ���, vector<unsigned char>  ��д���ļ�������);


#pragma region ȡ��ǰĿ¼

string ȡ��ǰĿ¼A();
wstring ȡ��ǰĿ¼W();
#ifdef _UNICODE
#define ȡ��ǰĿ¼() ȡ��ǰĿ¼A()
#else
#define ȡ��ǰĿ¼() ȡ��ǰĿ¼W()
#endif

#pragma endregion