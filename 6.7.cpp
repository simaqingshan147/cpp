//����ָ��
#include<iostream>
#include<string>
using std::string;

int main()
{
	bool lengthCompare(const string&, const string&);
	bool (*pf)(const string&, const string&);
	void ff(int*);
	void ff(unsigned int);

	pf = lengthCompare;
	pf = &lengthCompare;  //���������ȼ�

	bool b1 = pf("hello", "goodgye");  //���ú��������������ָ��
	bool b2 = (*pf)("hello", "goodbye");  //�ȼ�

	//����ָ��ɸ�Ϊ0��nullptr
	pf = 0;
	pf = nullptr;
	pf = lengthCompare;

	//ָ�����ͱ��������غ����е�ĳһ����ȷƥ��
	//void (*pf2)(int) = ff;  ����,û��ƥ�亯��

	//����ָ��ļ�д
	typedef bool Func(const string&, const string&);
	typedef decltype(lengthCompare)* Func2;  //���ߵȼ�
	Func2 pf2 = pf;
	Func* pf3 = pf;

	//����ָ������ָ��
	using F = int(int*, int);  //F�Ǻ������ͣ�����ָ��
	using FF = int (*)(int*, int);
	FF f1(int);
	// F f2(int);  ����,���ܷ��غ���
	int (*f2(int))(int*, int);  //f2 ����ָ�򷵻�int���͵ĺ�����ָ��
	auto f3(int)->int (*)(int*, int);  //β�÷�������

	string::size_type SumLength(const string&, const string&);
	decltype(SumLength)* getfcn(const string&);  
	//ʹ��decltype�ؼ��֣����غ������ͣ�����ʽ����*

	return 0;
}