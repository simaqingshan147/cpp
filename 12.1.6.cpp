//12.1.6  ---- weak_ptr
#include<iostream>
#include<string>
#include<memory>
using namespace std;

int main()
{
	//weakָ����shared_ptr����Ķ���
	shared_ptr<string> s(new string("hello"));
	cout << s.use_count() << endl;
	//������ָ���ʼ��
	weak_ptr<string> ws(s);
	cout << s.use_count() << endl;   //��weak���������ü���

	//lock�����ָ��Ķ������ü���Ϊ0�����ؿ�shared_ptr
	//���򷵻�ָ���������shared_ptr

	//���weak������ڴ��Ƿ��ͷ�,Ȼ���ʼ��s2
	if (shared_ptr<string> s2 = ws.lock())
		cout << *s2 << endl;

}