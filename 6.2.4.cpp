//�����β�
#include<iostream>
using std::cout;
using std::endl;

/*
* void print(const int*);
* void print(const int[]);
* void print(const int[10]);
* �����ȼ�
* ʵ�ʴ��ݵ���ָ��������Ԫ�ص�ָ��
*/

//ʹ�ñ��ָ�����鳤��
void print1(const char* cp)
{
	if (cp)
	{
		// \0����������
		while (*cp)
			cout << *cp++;
		cout << endl;
	}
}

//ʹ�ñ�׼��淶����ָ����Ԫ�غ�β��Ԫ�ص�ָ��
void print2(const int* beg, const int* end)
{
	//�������Ԫ�أ�������end
	while (beg != end)
		cout << *beg++ << ' ';
	cout << endl;
}

//��ʾ����һ����ʾ�����С���β�
void print3(const int ia[], size_t size)
{
	for (size_t i = 0; i != size; ++i)
		cout << ia[i] << ' ';
	cout << endl;
}