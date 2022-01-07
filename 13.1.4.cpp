//13.1.4 三五法则
#include<iostream>
#include<memory>
#include<vector>
#include<string>

using namespace std;

//三个基本操作控制类的拷贝
//新标准下五个


//需要析构函数的类也需要拷贝和赋值


class Ptr {
public:
	string* ps;
	Ptr(const string& s) {
		//ps为动态内存
		ps = new string(s);
	}

	//销毁动态内存需要析构函数
	~Ptr() { delete ps; }
};


//需要拷贝(构造函数)操作的类也需要赋值(=)操作，反之亦然

class numbered {
public:
	//默认构造函数
	numbered() { i = rand(); }

	numbered(const numbered& other) {
		i = rand();
		//不复制，而是生成新的
	}

	int i;
};

void f(const numbered& s) { cout << s.i << endl; }

int main()
{
	/*
	Ptr a("hello");
	Ptr b = a;  //合成拷贝赋值运算符

	//报错
	//因为合成拷贝函数或运算符只是简单拷贝指针
	//退出时=返回的Ptr会被脱离作用域，自动析构
	//则b的指针指向内存自动销毁，访问报错

	cout << *(a.ps) << endl;
	cout << *(b.ps) << endl;
	*/

	numbered a, b = a, c = b;

	//b,c由合成拷贝赋值运算符拷贝初始化
	f(a); f(b); f(c);  //3个41

	//定义了拷贝构造函数后
	//41,1836,77

	return 0;
}