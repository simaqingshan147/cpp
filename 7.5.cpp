//构造函数再探
#include<iostream>
#include<string>
using std::string;
using std::cout;

class ConstRef {
public:
	//正确的构造函数
	ConstRef(int ii):i(ii),ci(ii),ri(i){}

	//委托构造函数,把初始化职责委托给其他构造函数
	ConstRef() : ConstRef(3) {}
private:
	int i;
	const int ci;
	int& ri;
};

/*
* 没有在构造函数初始值列表中显式初始化成员
* 则该成员在构造函数体之前执行默认初始化
* 成员是const或引用,必须初始化
* 成员属于某类类型且该类没有定义默认构造函数时，必须初始化该成员
ConstRef::ConstRef(int ii)
{
	i = ii; 
	ci = ii;    //错误,不能给const赋值
	ri = i;     //错误,ri未初始化
}
*/

class X {
	int i;
	int j;
	//成员初始化顺序与它们在类定义中的出现顺序一致
	//构造函数初始值列表的顺序不会影响初始化顺序
public:
	//未定义:i在j前被初始化
	//i先定义,实际是用未定义的j定义i
	//X(int val) :j(val), i(j){}
};

//没有默认构造函数的类
class Nodefault {
public:
	Nodefault(const std::string&);
};

struct A {
	Nodefault my_men;   
};

//A a;  错误,无法为a初始化 

struct B {
	Nodefault b_member;
	//B(){}  错误,Nodefault没有默认构造函数
	//想默认构造B,必须先默认构造b_member
};

class C {
public:
	int a;
	string c;
	//只接受一个实参的构造函数,实际上定义了
	//转换为此类类型的隐式转换机制
	//转换构造函数
	C(string s):c(s),a(s.size()){}

	//将构造函数声明为explicit以阻止隐式转换
	//explicit只对一个实参的构造函数有效
	//explicit只能在类内声明中使用
	explicit C(const string s):c(s),a(s.size()){}
};

//C ac;
// 错误，编译器只会自动执行一步类型转换
// 字符串转换为string，再转换为类类型
// ac = C("string");

//const string s = "string";
//ac = C(s); 错误,不能隐式转换

//聚合类
//全部public
//无构造函数
//无类内初始值
struct Data {
	int ival;
	string s;
};

Data d = { 0,"string" };  //聚合类初始化
//d = {"string",0}    错误,顺序必须相同