//main:����������ѡ��
#include<iostream>
using std::endl;
using std::cout;

//argc �������ַ�������
//argv �洢C����ַ���������
//aggv ��һ��Ԫ���ǳ�����,���һ��ָ��֮���Ԫ��ֵβ0

int main(int argc, char* argv[])
{
	int i;
	for (i = 1; i < argc; i++)
		cout << *(argv[i]) << endl;

	return 0;
}

//6.2.5����->����->�������