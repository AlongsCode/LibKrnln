#pragma once
/*�Ƚ���Ҫ��ƽ̨�ض�������Ȼ���ں��Ŀ�֮��*/
#ifdef _WIN32
/*���ļ���Դ����������ʾ��ѡ��ָ���ļ�,�༭ģʽΪ����ѡ��ʱ��Ϊ������ģʽ*/
bool ��λ�ļ�(const std::wstring& �ļ�·��, bool �༭ģʽ = false);
bool ��λ�ļ�(const std::string& �ļ�·��, bool �༭ģʽ = false);

long long ȡ����ʣ��ռ�(char �����������ַ�);
long long ȡ����ʣ��ռ�(wchar_t �����������ַ�);
long long ȡ����ʣ��ռ�(const std::wstring& �����������ַ� = L"");
long long ȡ����ʣ��ռ�(const std::string& �����������ַ�);

bool �ô��̾��(const std::string& �����������ַ�, const std::string& ������ľ���ı� = "");
bool �ô��̾��(const std::wstring& �����������ַ� = L"", const std::wstring& ������ľ���ı� = L"");
bool �ô��̾��(char �����������ַ�, const std::string& ������ľ���ı� = "");
bool �ô��̾��(wchar_t �����������ַ�, const std::wstring& ������ľ���ı� = L"");

std::string ȡ���̾��A(char �����������ַ�);
std::wstring ȡ���̾��W(wchar_t �����������ַ�);
std::string ȡ���̾��A(const std::string& �����������ַ� = "");
std::wstring ȡ���̾��W(const std::wstring& �����������ַ� = L"");


long long ȡ�����ܿռ�(wchar_t �����������ַ�);
long long ȡ�����ܿռ�(char �����������ַ�);
long long ȡ�����ܿռ�(const std::wstring& �����������ַ� = L"");
long long ȡ�����ܿռ�(const std::string& �����������ַ�);

/*���̲��� - ���ļ�����
	���ø�ʽ�� ���߼��͡� ���ļ����� ���ı��� �����������Ե��ļ����ƣ������� ������Ϊ������ֵ�� - ϵͳ����֧�ֿ�->���̲���
	Ӣ�����ƣ�SetAttr
	Ϊһ���ļ�����������Ϣ���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
	����<1>������Ϊ�������������Ե��ļ����ơ�������Ϊ���ı��ͣ�text������
	����<2>������Ϊ��������Ϊ������ֵ��������Ϊ�������ͣ�int����������ֵ����Ϊ���³���ֵ����ͣ� 1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 32��#�浵�ļ� ��ͨ������Щ����ֵ����������һ�����ö���ļ����ԡ�
*/
bool ���ļ�����(const std::wstring& �����������Ե��ļ�����, int ������Ϊ������ֵ);
/*���̲��� - ���ļ�����
	���ø�ʽ�� ���߼��͡� ���ļ����� ���ı��� �����������Ե��ļ����ƣ������� ������Ϊ������ֵ�� - ϵͳ����֧�ֿ�->���̲���
	Ӣ�����ƣ�SetAttr
	Ϊһ���ļ�����������Ϣ���ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
	����<1>������Ϊ�������������Ե��ļ����ơ�������Ϊ���ı��ͣ�text������
	����<2>������Ϊ��������Ϊ������ֵ��������Ϊ�������ͣ�int����������ֵ����Ϊ���³���ֵ����ͣ� 1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 32��#�浵�ļ� ��ͨ������Щ����ֵ����������һ�����ö���ļ����ԡ�
*/
bool ���ļ�����(const std::string& �����������Ե��ļ�����, int ������Ϊ������ֵ);
#pragma region ȡ���̾��

#ifdef _UNICODE
#define ȡ���̾��() ȡ���̾��A()
#else
#define ȡ���̾��() ȡ���̾��W()
#endif

#else
#endif



/*ȫƽ̨ͨ�ú���*/
bool �ı�������(const std::string& ���ı䵽��������);
bool �ı�������(const std::wstring& ���ı䵽��������);
bool �ı�������(char ���ı䵽��������);
bool �ı�������(wchar_t ���ı䵽��������);

bool �ı�Ŀ¼(const std::string& ���ı䵽��Ŀ¼);
bool �ı�Ŀ¼(const std::wstring& ���ı䵽��Ŀ¼);

/*ǿ�ƴ����Ὣ�����ڸ�Ŀ¼��Ŀ¼�д����ļ�*/
bool ����Ŀ¼(const std::string& ��������Ŀ¼����, bool ǿ�ƴ��� = false);
/*ǿ�ƴ����Ὣ�����ڸ�Ŀ¼��Ŀ¼�д����ļ�*/
bool ����Ŀ¼(const std::wstring& ��������Ŀ¼����, bool ǿ�ƴ��� = false);


bool ɾ��Ŀ¼(const std::string& ��ɾ����Ŀ¼����);
bool ɾ��Ŀ¼(const std::wstring& ��ɾ����Ŀ¼����);

bool �����ļ�(const std::string& �����Ƶ��ļ���, const std::string& ���Ƶ����ļ���);
bool �����ļ�(const std::wstring& �����Ƶ��ļ���, const std::wstring& ���Ƶ����ļ���);

bool �ƶ��ļ�(const std::wstring& ���ƶ����ļ�, const std::wstring& �ƶ�����λ��);
bool �ƶ��ļ�(const std::string& ���ƶ����ļ�, const std::string& �ƶ�����λ��);

bool ɾ���ļ�(const std::wstring& ��ɾ�����ļ���);
bool ɾ���ļ�(const std::string& ��ɾ�����ļ���);

bool �ļ�����(const std::wstring& ��������ԭ�ļ���Ŀ¼��, const std::wstring& ������Ϊ�����ļ���Ŀ¼��);
bool �ļ�����(const std::string& ��������ԭ�ļ���Ŀ¼��, const std::string& ������Ϊ�����ļ���Ŀ¼��);

bool �ļ��Ƿ����(const std::string& �����Ե��ļ�����);
bool �ļ��Ƿ����(const std::wstring& �����Ե��ļ�����);
//�������������Ѱ���ļ�����һ���������������ڵ��ڴ棬�벻��ʱ��ʱ�ͷ�;
std::string Ѱ���ļ�(std::string ��Ѱ�ҵ��ļ���Ŀ¼���� = "", int ��Ѱ���ļ������� = 0);
std::wstring Ѱ���ļ�(const std::wstring& ��Ѱ�ҵ��ļ���Ŀ¼���� = L"", int ��Ѱ���ļ������� = 0);

std::tm ȡ�ļ�ʱ��(const std::string& �ļ���);
std::tm ȡ�ļ�ʱ��(const std::wstring& �ļ���);

int ȡ�ļ�����(const std::string& �ļ���);
int ȡ�ļ�����(const std::wstring& �ļ���);

long long ȡ�ļ��ߴ�(const std::wstring& �ļ���);
long long ȡ�ļ��ߴ�(const std::string& �ļ���);
#define ȡ�ļ���С(�ļ���) ȡ�ļ��ߴ�(�ļ���);




//Ĭ���������Ŀ¼�����Ϳ���ָ��Ϊ�����ļ����ͣ���"txt"
bool ���Ŀ¼(const std::string& Ҫɾ���ļ���Ŀ¼, const std::string& �ļ����� = "", bool ɾ���ļ��� = true);
//Ĭ���������Ŀ¼�����Ϳ���ָ��Ϊ�����ļ����ͣ���"txt"
bool ���Ŀ¼(const std::wstring& Ҫɾ���ļ���Ŀ¼, const std::wstring& �ļ����� = L"", bool ɾ���ļ��� = true);
std::string ȡ��ʱ�ļ���A(const std::string& Ŀ¼�� = "");
std::wstring ȡ��ʱ�ļ���W(const std::wstring& Ŀ¼�� = L"");
#pragma region ȡ��ʱ�ļ���
std::string ȡ��·��(const std::string& ��ȡ��·����Ŀ¼���ļ�);
std::wstring ȡ��·��(const std::wstring& ��ȡ��·����Ŀ¼���ļ�);
#ifdef _UNICODE
#define ȡ��ʱ�ļ���() ȡ��ʱ�ļ���A()
#else
#define ȡ��ʱ�ļ���() ȡ��ʱ�ļ���W()
#endif

#pragma endregion

std::vector<unsigned char> �����ļ�(const std::string& �ļ���);
std::vector<unsigned char> �����ļ�(const std::wstring& �ļ���);


bool д���ļ�(const std::string& �ļ���, std::vector<unsigned char>  ��д���ļ�������);
bool д���ļ�(const std::wstring& �ļ���, std::vector<unsigned char>  ��д���ļ�������);


#pragma region ȡ��ǰĿ¼

std::string ȡ��ǰĿ¼A();
std::wstring ȡ��ǰĿ¼W();
#ifdef _UNICODE
#define ȡ��ǰĿ¼() ȡ��ǰĿ¼A()
#else
#define ȡ��ǰĿ¼() ȡ��ǰĿ¼W()
#endif

#pragma endregion