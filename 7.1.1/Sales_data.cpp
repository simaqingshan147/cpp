//���Sales_data��
#include<Sales_data.h>

//struct Sales_data {
//	//���ݳ�Ա
//	string bookNo;
//	unsigned units_sold = 0;
//	double revenue = 0.0;
//	
//	string isbn() const { return bookNo; }; //������Ա����
	/*
	isbn��Ա������ʹ�õ������
	����a.isbn()
	ʵ����,��Ա����ͨ��һ�����ε�this�����βη��ʵ������Ķ���(a)
	this����ָ����ö����ָ��
	α����:sales_data::isbn(this��&a)
	this���ζ���,�����Զ���this����������Ƿ�
	*/

	/*
	* isbn������const�ؼ���
	* this��ָ�������ͷǳ����汾�ĳ���ָ��
	* �� Sales_data *const(����const,ָ�벻��)
	* Ĭ������£����ܰ�this�󶨵�һ������������
	*��const���ڳ�Ա�����Ĳ����б�֮��,��ʾthis��һ��ָ������ָ��
	* ��this�޸�Ϊ const Sales_data *const
	* ����this����ָ����,��Ա�������ܱ�����
	* ����ʹ��const�ĺ����г�����Ա����
	*/
//	Sales_data& combine(const Sales_data&);
//	double avg_price() const;

	//���캯��
//	Sales_data() = default;  //�������κ�ʵ��,Ĭ�Ϲ��캯��
//	Sales_data(const string&s):bookNo(s){}  //�������ݳ�ԱĬ�ϳ�ʼ��
//	Sales_data(const string&s,unsigned n,double p):
//		bookNo(s),units_sold(n),revenue(p*n){}
//	Sales_data(istream&);
//};



int main()
{
	Sales_data a, b;
	a = Sales_data("Boble", 100, 20.5);
	b = Sales_data("Fuck you", 300, 123.4);
	print(cout, a);
	cout << endl;
	cout << a.isbn() << endl;
	print(cout, b);
	cout << endl;
	a = add(a, b);
	print(cout, a);

	return 0;
}