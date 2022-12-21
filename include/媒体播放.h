#pragma once

bool ��������(const vector<unsigned char>& �����ŵ�����, bool �Ƿ�ѭ������ = false, bool �Ƿ�ͬ������ = false);
bool ��������(const string& �����ŵ�����, bool �Ƿ�ѭ������ = false, bool �Ƿ�ͬ������ = false);
bool ��������(const wstring& �����ŵ�����, bool �Ƿ�ѭ������ = false, bool �Ƿ�ͬ������ = false);

bool ֹͣ����();


#pragma region �Ǳ�©�ӿ�
namespace KrnlnMidInside {
	struct MIDIFILEDATAINFO
	{
		unsigned char* pData;
		size_t	dwSize;
	};
	//�ַ���0�����ַ���1������ָ��2;
	struct MIDMUSIC
	{
		union {
			const char* name;
			const wchar_t* wname;
			MIDIFILEDATAINFO data;
		};
		int datatype;
	};
	void PackMid(vector<MIDMUSIC>& MidStruct, string MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, wstring MemData);
	void PackMid(vector<MIDMUSIC>& MidStruct, vector<unsigned char> MemData);
	void PlayMid(int times, int interval, vector<MIDMUSIC> wannaplay);
}
#pragma endregion
template <class... T>
void ����MID(int ���Ŵ���, int ���ʱ��, T... ������MID)
{
	vector<KrnlnMidInside::MIDMUSIC> Data;
	std::initializer_list<INT>{(PackMid(Data, std::forward<T>(������MID)), 0)...};
	KrnlnMidInside::PlayMid(���Ŵ���, ���ʱ��, Data);
};
