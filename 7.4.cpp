//类的作用域
#include<iostream>
#include<string>
using std::string;

typedef double Money;
string bal;

class Account {
public:
	//名字如果在类中不存在
	//会在定义类的作用域中寻找
	Money balance() { return bal; }
	//return Money bal
	//因为类首先编译成员声明
	//然后编译函数体
	//函数能使用类中定义的任何名字
private:
	//typedef char Money;  错误，应声明在类开始处
	Money bal;
};