//11.4 �������� ���򣨹�ϣ������
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>
#include<unordered_set>
using namespace std;

//����������ɢ��ʵ��
//��ͻ����������������(?)

class myCla {
public:
	string str;
	int num;
};

//�ж����
bool isSame(myCla& a, myCla& b) { return a.num == b.num; }

//�Խ�hash����
//string���͵�hashֵ
//hash�Ǹ�ģ��(��)
size_t hasher(const myCla& a) { return hash<string>()(a.str); }


int main()
{
	//��������������ʱ��ֱ�Ӷ���
	//��Ϊ�����������Լ���hash�����ͱȽ���ȵķ���
	unordered_map<string,string> myMap;
	unordered_multiset<int> aset(32);  //ÿ������ڵ�ĸ���
	unordered_multiset<int> bset;      //��ָ��Ҳ��

	//����Ϊ�Լ����set����һ�����ͱ���
	//�Խ���������������ָ��hash�����ͱȽ���ȵĺ���
	using myCla_mutiset = 
		unordered_multiset<myCla, decltype(hasher)*, decltype(isSame)*>;

	//ÿ������ڵ�ĸ���,��ϣ����ָ��,����жϺ���ָ��
	//�Խ��ı���ָ������ڵ����
	myCla_mutiset myset(42,hasher, isSame);  //��ʽ����
	myCla a = { "string",1 };
	//myCla b("string", 1); ��Ҫ���캯��
	myCla b; b.str = "string"; b.num = 2;
	
	//ʹ��
	myset.insert(a);
	myset.insert(b);

	return 0;
}