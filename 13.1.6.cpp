//13.1.6 -- ��ֹ����
#include<iostream>
#include<string>

using namespace std;


//��ֹ����
struct Nocopy {
	int a;
	string s;

	Nocopy() = default; //�ϳ�Ĭ�Ϲ��캯��
	Nocopy(Nocopy&) = delete;  //��ֹ����
	Nocopy& operator=(const Nocopy&) = delete;  //��ֹ��ֵ

	~Nocopy() = default;
};

//��ֹ����
struct Noerase {
	int a;
	string s;

	Noerase() = default; //�ϳ�Ĭ�Ϲ��캯��

	~Noerase() = delete;  //��ֹ����
};

int main()
{
	Nocopy test;
	test.a = 1; test.s = "hello";

	//Nocopy test2(test);
	//Nocopy test2 = test;

	//��ֹ�������������޷��������
	//Noerase a;

	//�����Զ�̬�������
	Noerase* p = new Noerase();
	//������ɾ��
	//delete p;

	return 0;
}