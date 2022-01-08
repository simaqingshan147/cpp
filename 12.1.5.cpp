//12.1.5 ---- unique_ptr
#include<iostream>
#include<string>
#include<memory>
using namespace std;

//unique_ptr ��ռָ�����
//��ָ�����٣�ָ���ڴ�Ҳ����

void fcn1()
{
	//*ptr = 42;
	unique_ptr<int> uptr(new int(42));
	unique_ptr<int> uptr2(new int(42));
	unique_ptr<int> uptr3(new int(42));
	unique_ptr<int> uptr4(new int(42));

	//��Ϊ��ռ�������Բ�֧�ֿ�����ֵ
	//unique_ptr<int> p3(uptr);  ���ܿ���
	//unique_ptr<int> p3 = uptr;  ���ܸ�ֵ

	uptr = nullptr;  //�ͷŶ���,uptrΪ��
	int* ptr = uptr2.release();  //uptr2��������Ȩ,������ָͨ�룬�ÿ�
	uptr3.reset();  //�ͷŶ���
	uptr3.reset(ptr);  //�ͷ�ԭ����ָ��ptr

	//����Ȩת��
	unique_ptr<string> ptrs1(new string("hello"));
	unique_ptr<string> ptrs2(ptrs1.release());  //ת�Ƹ�ptrs2

	unique_ptr<string> ptrs3(new string("hello"));
	ptrs3.reset(ptrs2.release());  //ת�Ƹ�ptrs3
}

void fcn2()
{
	shared_ptr<int> p1 = make_shared<int>(42);
	shared_ptr<int> p2(p1);
	shared_ptr<int> p3(p2);

	cout << "p1: " << p1.use_count() << endl;
	cout << "p2: " << p2.use_count() << endl;
	cout << "p3: " << p3.use_count() << endl;
	p3.reset();
	cout << "p1: " << p1.use_count() << endl;
	cout << "p2: " << p2.use_count() << endl;
	cout << "p3: " << p3.use_count() << endl;

}

int main()
{

	return 0;
}