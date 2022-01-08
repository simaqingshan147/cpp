//类的静态成员
//有时类需要一些成员与类本身相关，而不是与各个对象关联
#include<iostream>
#include<string>
using std::string;

//银行账户记录类
class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double rate() { return interestRate; }
	static void rate(double);
private:
	string owner;
	double amount;
	static double interestRate;    //利率
	static constexpr int period = 30;  //constexper静态成员可以类内初始化
	static double initRate();
};

//类外定义静态成员
void Account::rate(double newRate)
{
	//类外定义静态成员,不能重复static关键字
	interestRate = newRate;
}

int main()
{
	//所有account对象共有静态成员
	double r;
	r = Account::rate();   //使用作用域运算符访问静态成员
	
	Account ac1;
	Account* ac2 = &ac1;
	r = ac1.rate();
	r = ac2->rate();
}

//因为static成员独立于任何对象

class Bar {
	//static成员可以是不完全类型,如自身的类类型
	static Bar men1;
	Bar* men2;   //指针可以是不完全类型
	//Bar men3;   数据成员必须是完整类型
};

class C {
public:
	int a;
	static int b;
	//可以使用静态成员作为默认实参
	int function(int d = b) { return d; }
};