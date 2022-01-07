//13.1 类的拷贝，赋值与销毁
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class foo {
public:
	foo() {
		a = 0;
		s = "";
	}
	foo(const int i, const string& j) {
		a = i; s = j;
	}

	//拷贝构造函数,第一个参数是自身引用
	//没有编译器会定义一个
	foo(const foo& other) {
		a = other.a;
		s = other.s;
	}

	//重载运算符，本质上是函数
	//如果运算符是成员函数，左侧对象绑定this
	//赋值运算符应与默认赋值保持一致，返回左侧对象的引用
	foo& operator=(const foo& other) {
		a = other.a; s = other.s;
	}

	//析构函数，不接受参数，无法重载
	// 没有，编译器合成析构函数，函数体为空(除了销毁什么都不执行)
	//首先执行函数体，然后按初始化顺序的逆序销毁
	~foo() {
		cout << "bye" << endl;
	}
	//所以析构函数本身不销毁
	//销毁阶段在构造函数后隐含

	int a;
	string s;
};



int main()
{
	foo b(12,"hello");

	//编译器合成拷贝赋值运算符
	foo a = b;  //拷贝初始化
	return 0;
}