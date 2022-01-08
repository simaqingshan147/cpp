//设计Sales_data类
#include<Sales_data.h>

//struct Sales_data {
//	//数据成员
//	string bookNo;
//	unsigned units_sold = 0;
//	double revenue = 0.0;
//	
//	string isbn() const { return bookNo; }; //常量成员函数
	/*
	isbn成员调用是使用点运算符
	形如a.isbn()
	实际上,成员函数通过一个隐形的this额外形参访问调用它的对象(a)
	this既是指向调用对象的指针
	伪代码:sales_data::isbn(this或&a)
	this隐形定义,所以自定义this参数或变量非法
	*/

	/*
	* isbn定义后的const关键字
	* this是指向类类型非常量版本的常量指针
	* 即 Sales_data *const(顶层const,指针不变)
	* 默认情况下，不能把this绑定到一个常量对象上
	*把const放在成员函数的参数列表之后,表示this是一个指向常量的指针
	* 即this修改为 const Sales_data *const
	* 这样this就能指向常量,成员函数就能被调用
	* 这样使用const的函数叫常量成员函数
	*/
//	Sales_data& combine(const Sales_data&);
//	double avg_price() const;

	//构造函数
//	Sales_data() = default;  //不接受任何实参,默认构造函数
//	Sales_data(const string&s):bookNo(s){}  //其他数据成员默认初始化
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