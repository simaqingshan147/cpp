//13.1.4 ���巨��
#include<iostream>
#include<memory>
#include<vector>
#include<string>

using namespace std;

//������������������Ŀ���
//�±�׼�����


//��Ҫ������������Ҳ��Ҫ�����͸�ֵ


class Ptr {
public:
	string* ps;
	Ptr(const string& s) {
		//psΪ��̬�ڴ�
		ps = new string(s);
	}

	//���ٶ�̬�ڴ���Ҫ��������
	~Ptr() { delete ps; }
};


//��Ҫ����(���캯��)��������Ҳ��Ҫ��ֵ(=)��������֮��Ȼ

class numbered {
public:
	//Ĭ�Ϲ��캯��
	numbered() { i = rand(); }

	numbered(const numbered& other) {
		i = rand();
		//�����ƣ����������µ�
	}

	int i;
};

void f(const numbered& s) { cout << s.i << endl; }

int main()
{
	/*
	Ptr a("hello");
	Ptr b = a;  //�ϳɿ�����ֵ�����

	//����
	//��Ϊ�ϳɿ��������������ֻ�Ǽ򵥿���ָ��
	//�˳�ʱ=���ص�Ptr�ᱻ�����������Զ�����
	//��b��ָ��ָ���ڴ��Զ����٣����ʱ���

	cout << *(a.ps) << endl;
	cout << *(b.ps) << endl;
	*/

	numbered a, b = a, c = b;

	//b,c�ɺϳɿ�����ֵ�����������ʼ��
	f(a); f(b); f(c);  //3��41

	//�����˿������캯����
	//41,1836,77

	return 0;
}