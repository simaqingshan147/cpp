//12.1.3 shared_ptr��new���ʹ��
#include<iostream>
#include<memory>
using namespace std;

void fcn1()
{
	//��new���ص�ָ���ʼ������ָ��
	shared_ptr<int> i(new int(42));

	//����ָ�����������ָ�빹�캯����explicit��
	//������ʹ��ֱ�ӳ�ʼ������ʼ������ָ��
	//shared_ptr<int> i2 = new int(42);   ����,��ʽת��

	int num = 42;
	int* p2 = &num;
	
	//Ĭ�ϰ󶨶�̬�ڴ浽����ָ��
	//��Ϊ����ָ����delete�ͷŹ�������
	shared_ptr<int> i2(p2);  //delete�Ƕ�̬�ڴ棬δ����
}

void process(shared_ptr<int> ptr) { cout << *ptr << endl; }

//��Ҫ���ʹ����ָͨ�������ָ��
void fcn2()
{
	shared_ptr<int> p(new int(42));  //*p = 42

	//��ȷ
	//p���Ƹ��βΣ����ü�����һ,�뿪���������βΣ����ô���Ϊ1
	process(p);
	cout << p.use_count() << endl;   //1

	int* x(new int(1024));  //��ָͨ��

	//process(x) ����,������ʽת��int*Ϊ����ָ��

	//�Ϸ�,��x�ڴ汻�ͷ�
	//p = shared<int>(x)�����ô���Ϊ1
	//�뿪����p���٣����ô���Ϊ0���Զ��ͷ�xָ����ڴ�
	process(shared_ptr<int>(x));
	//cout << *x << endl; �ڴ汻�ͷ�!!!
}

//����shared_ptr����
void fcn3()
{
	shared_ptr<int> p(new int(10));  //*p = 10;

	//reset���������ü���,����ָ��ָ�����
	//���ԭ���ü���Ϊ0������ԭָ�����

	p.reset(new int(1024));  //10������

	//�ı�ײ����ǰ������Լ��Ƿ���Ψһָ���ָ��
	if (!p.unique())
		p.reset(new int(*p));
	//��ԭֵ������������p�ĸ��²���Ӱ������ָ��1024��ָ��
	*p += 1024;  //���¶���ֵ
}