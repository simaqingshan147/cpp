//�����string����
#include<iostream>
#include<string>
using namespace std;

//string����
void knowledge1()
{
	string a;
	a = "string";
	char str[12] = "string";
	str[6] = '\0';

	string b(str, 12);   //��������,���������ٰ���12��Ԫ��
	string c(a, 0);     //c��a���±�0��ʼ�Ŀ���
	string d(a, 0, 6);  //���±�0��ʼ����a����������Ϊ6
	//string e(a, 100, 6);    //�±곬����δ����,�׳�out_of_range
	string e(a, 0, 100);     //ֻ��������β
}

//substr
void knowledge2()
{
	//substr(beg,length)
	//beg��ʼ�ַ��±�
	//length������λ��������ֻ��������β

	//substr(n)
	//���±�n��ʼ���Ƶ���β

	string s("hello world");
	string s2 = s.substr(0, 5);
	string s3 = s.substr(6);
	string s4 = s.substr(12);   //out_of_range
}

int main()
{
	return 0;
}