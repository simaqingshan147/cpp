//���԰���
#include<iostream>
#include<cassert>
using std::cout;
using std::endl;
using std::cerr;

void print(const int ia[], size_t size)
{
	//δ����NDEBUGʱ
	#ifndef NDEBUG
	//__func__��ź�����
	cerr << __func__ << ": array size is " << size << endl;
	#endif
	for (int i = 0; i < size; ++i)
		cout << ia[i] << ' ';
	cout << endl;
}

int main()
{
	int num[5] = { 1,2,3,4,5 };
	assert(num[0] != 1);  //�����������Զ�ֹͣ
	print(num, 5);
	return 0;
}