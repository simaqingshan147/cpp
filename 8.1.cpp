//IO��
//��������ڱʼǱ���
#include<iostream>
using namespace std;

int main()
{
	cin.tie(&cout);        //��׼�⽫cin��cout������һ��
	ostream* old_tie = cin.tie(nullptr);     //cin������
	cin.tie(&cerr);                          //cin����cerr
	cin.tie(old_tie);                        //�ؽ�cin��cout�Ĺ���

	return 0;
}