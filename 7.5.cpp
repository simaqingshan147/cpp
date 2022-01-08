//���캯����̽
#include<iostream>
#include<string>
using std::string;
using std::cout;

class ConstRef {
public:
	//��ȷ�Ĺ��캯��
	ConstRef(int ii):i(ii),ci(ii),ri(i){}

	//ί�й��캯��,�ѳ�ʼ��ְ��ί�и��������캯��
	ConstRef() : ConstRef(3) {}
private:
	int i;
	const int ci;
	int& ri;
};

/*
* û���ڹ��캯����ʼֵ�б�����ʽ��ʼ����Ա
* ��ó�Ա�ڹ��캯����֮ǰִ��Ĭ�ϳ�ʼ��
* ��Ա��const������,�����ʼ��
* ��Ա����ĳ�������Ҹ���û�ж���Ĭ�Ϲ��캯��ʱ�������ʼ���ó�Ա
ConstRef::ConstRef(int ii)
{
	i = ii; 
	ci = ii;    //����,���ܸ�const��ֵ
	ri = i;     //����,riδ��ʼ��
}
*/

class X {
	int i;
	int j;
	//��Ա��ʼ��˳�����������ඨ���еĳ���˳��һ��
	//���캯����ʼֵ�б��˳�򲻻�Ӱ���ʼ��˳��
public:
	//δ����:i��jǰ����ʼ��
	//i�ȶ���,ʵ������δ�����j����i
	//X(int val) :j(val), i(j){}
};

//û��Ĭ�Ϲ��캯������
class Nodefault {
public:
	Nodefault(const std::string&);
};

struct A {
	Nodefault my_men;   
};

//A a;  ����,�޷�Ϊa��ʼ�� 

struct B {
	Nodefault b_member;
	//B(){}  ����,Nodefaultû��Ĭ�Ϲ��캯��
	//��Ĭ�Ϲ���B,������Ĭ�Ϲ���b_member
};

class C {
public:
	int a;
	string c;
	//ֻ����һ��ʵ�εĹ��캯��,ʵ���϶�����
	//ת��Ϊ�������͵���ʽת������
	//ת�����캯��
	C(string s):c(s),a(s.size()){}

	//�����캯������Ϊexplicit����ֹ��ʽת��
	//explicitֻ��һ��ʵ�εĹ��캯����Ч
	//explicitֻ��������������ʹ��
	explicit C(const string s):c(s),a(s.size()){}
};

//C ac;
// ���󣬱�����ֻ���Զ�ִ��һ������ת��
// �ַ���ת��Ϊstring����ת��Ϊ������
// ac = C("string");

//const string s = "string";
//ac = C(s); ����,������ʽת��

//�ۺ���
//ȫ��public
//�޹��캯��
//�����ڳ�ʼֵ
struct Data {
	int ival;
	string s;
};

Data d = { 0,"string" };  //�ۺ����ʼ��
//d = {"string",0}    ����,˳�������ͬ