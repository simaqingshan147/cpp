//ǿ������ת��
#include<iostream>
using std::cout;
using std::endl;

int main(void)
{
	//static_cast
	//���ں�������ʧ
	long double j = 3.14159265357;
	double slope = static_cast<double>(j);

	void* p1 = &j; //void*����ָ���κ�����
	//�һش���void*ָ���е�ֵ
	//warning:ת��������ͱ�����ָ��ԭ����ָ������
	long double* dp = static_cast<long double*>(p1);

	//const_cast
	//ȥ���Ͳ�const
	const char* cp;
	char* p2 = const_cast<char*>(cp);

	//reinterpret_cast
	int* ip;
	char* pc = reinterpret_cast<char*>(ip);
	//��ͬ��c������ת��
	char* pc2 = (char*)ip;

	return 0;
}