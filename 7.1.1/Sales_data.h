#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

typedef string bookNo;

class Sales_data {
	//��Ԫ����������������������ķǹ��г�Ա
	//���ܷ��ʿ��Ƽ����Լ��
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend istream& read(istream&, Sales_data&);
	friend ostream& print(ostream&, const Sales_data&);
public:
	Sales_data() = default;
	Sales_data(const string& s) :bookNo(s) {}
	Sales_data(const string& s, unsigned n, double p) :
		bookNo(s), units_sold(n), revenue(p* n) {}
	Sales_data(istream&);
	string isbn()const { return bookNo; }
	Sales_data& combine(const Sales_data&);

private:
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
	double avg_price()const;
};

//��Ԫ����������Ԫ����֮�⣬�����ⲿ�ٴ�����
Sales_data add(const Sales_data&, const Sales_data&);
istream& read(istream&, Sales_data&);
ostream& print(ostream&, const Sales_data&);

//�����ⶨ�幹�캯��
//���캯����ʼֵ�б�Ϊ��
Sales_data::Sales_data(istream& is)
{
	read(is, *this);
	//���캯���޷�������
}

//�ⲿ���庯��,������Ա����
double Sales_data::avg_price() const {
	//����λ�������������
	//�����ܹ�ʹ�����Ա

	if (units_sold)
		return revenue / units_sold;

	return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;  //���ص��øú����Ķ���
}

//���к�������Ľӿڣ����������Ա

//����Ľ�����Ϣ����isbn���۳��������۳��۸�
//IO�಻�ܱ�����,ֻ�������ô���
istream& read(istream& is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

ostream& print(ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	//��������
	//�������Ӧ�������ٶԸ�ʽ�Ŀ���,��ʽ��user����
	return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}