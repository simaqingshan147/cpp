#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

typedef string bookNo;

class Sales_data {
	//友元，允许其他类或函数访问它的非公有成员
	//不受访问控制级别的约束
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

//友元函数需在友元声明之外，在类外部再次声明
Sales_data add(const Sales_data&, const Sales_data&);
istream& read(istream&, Sales_data&);
ostream& print(ostream&, const Sales_data&);

//在类外定义构造函数
//构造函数初始值列表为空
Sales_data::Sales_data(istream& is)
{
	read(is, *this);
	//构造函数无返回类型
}

//外部定义函数,常量成员函数
double Sales_data::avg_price() const {
	//代码位于类的作用域内
	//所以能够使用类成员

	if (units_sold)
		return revenue / units_sold;

	return 0;
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;  //返回调用该函数的对象
}

//下列函数是类的接口，但不是类成员

//输入的交易信息包括isbn，售出总数和售出价格
//IO类不能被拷贝,只能用引用传递
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
	//不负责换行
	//输出函数应尽量减少对格式的控制,格式由user决定
	return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}