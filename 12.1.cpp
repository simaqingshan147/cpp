//12.1 ---- ��̬�ڴ�������ָ��
#include<iostream>
#include<string>
#include<memory>
using namespace std;

//����ָ��ģ��
void fcn1()
{
	//shared_ptr��
	shared_ptr<string> p1;  //��ָ��
	if (p1&&p1->empty())  //������string��empty
		*p1 = "string";  //�����ã���ֵ
	

	//��ȫ�ķ����ʹ�ö�̬�ڴ�
	//make_shared���������еĲ��������ܳ�ʼ����������

	//int *iptr = new int(42) iptr��ָ��42��ָ��
	shared_ptr<int> iptr = make_shared<int>(42);
	//string* sptr = new string*("9999999999")
	shared_ptr<string> sptr = make_shared<string>(10, '9');

	//shared_str������ֵ
	//shared_strÿ������һ�Σ�ָ��������ü�����һ
	//shared_str��������ֵ������,ָ��������ü�����һ
	cout << "iptr���ô���Ϊ" << iptr.use_count() << endl;  //1
	auto q(iptr);
	cout << "iptr���ô���Ϊ" << iptr.use_count() << endl;  //2
	cout << "q�����ô���Ϊ" << q.use_count() << endl;    //2
}

int main()
{
	fcn1();
	return 0;
}