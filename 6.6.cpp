//����ƥ��
#include<iostream>
using std::cout;
using std::endl;

void f()
{
	cout << 0 << endl;
}

void f(int)
{
	cout << 1 << endl;
}

void f(int, int=2)
{
	cout << 2 << endl;
}

void f(double, double=3.14)
{
	cout << 3 << endl;
}

//������������
void ff(int)
{
	cout << "f1" << endl;
}

void ff(short)
{
	cout << "f2" << endl;
}

//������������ת��
void manip(long)
{
	cout << "m1" << endl;
}
void manip(double)
{
	cout << "m2" << endl;
}

int main()
{
	f(5.6);  
	//f(int),f(d,d)����
	//f(d,d)���ƥ��

	//f(4);
	//û��һ�����ƥ��(f(int)��f(int,int)�����),�����Դ���

	//��ΪС����һ��������int
	short int a = 1;
	ff('a');
	ff(a);

	//������������ת���ļ�����ͬ
	//ת����double��long������ͬ��Ӧ����
	//��������������vs2019������
	manip(3.14);

	return 0;
}