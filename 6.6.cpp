//函数匹配
#include<iostream>
using std::cout;
using std::endl;

void f()
{
	cout << 0 << endl;
}

void f(int)
{
	cout << 1 << endl;
}

void f(int, int=2)
{
	cout << 2 << endl;
}

void f(double, double=3.14)
{
	cout << 3 << endl;
}

//关于类型提升
void ff(int)
{
	cout << "f1" << endl;
}

void ff(short)
{
	cout << "f2" << endl;
}

//关于算术类型转换
void manip(long)
{
	cout << "m1" << endl;
}
void manip(double)
{
	cout << "m2" << endl;
}

int main()
{
	f(5.6);  
	//f(int),f(d,d)可行
	//f(d,d)最佳匹配

	//f(4);
	//没有一个最佳匹配(f(int)和f(int,int)都最佳),二义性错误

	//因为小整型一般提升到int
	short int a = 1;
	ff('a');
	ff(a);

	//所有算术类型转换的级别相同
	//转换到double或long级别相同，应报错
	//这个不报错可能是vs2019的特性
	manip(3.14);

	return 0;
}