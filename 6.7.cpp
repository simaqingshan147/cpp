//函数指针
#include<iostream>
#include<string>
using std::string;

int main()
{
	bool lengthCompare(const string&, const string&);
	bool (*pf)(const string&, const string&);
	void ff(int*);
	void ff(unsigned int);

	pf = lengthCompare;
	pf = &lengthCompare;  //两个声明等价

	bool b1 = pf("hello", "goodgye");  //调用函数，无需解引用指针
	bool b2 = (*pf)("hello", "goodbye");  //等价

	//函数指针可赋为0或nullptr
	pf = 0;
	pf = nullptr;
	pf = lengthCompare;

	//指针类型必须于重载函数中的某一个精确匹配
	//void (*pf2)(int) = ff;  错误,没有匹配函数

	//函数指针的简写
	typedef bool Func(const string&, const string&);
	typedef decltype(lengthCompare)* Func2;  //两者等价
	Func2 pf2 = pf;
	Func* pf3 = pf;

	//返回指向函数的指针
	using F = int(int*, int);  //F是函数类型，不是指针
	using FF = int (*)(int*, int);
	FF f1(int);
	// F f2(int);  错误,不能返回函数
	int (*f2(int))(int*, int);  //f2 返回指向返回int类型的函数的指针
	auto f3(int)->int (*)(int*, int);  //尾置返回类型

	string::size_type SumLength(const string&, const string&);
	decltype(SumLength)* getfcn(const string&);  
	//使用decltype关键字，返回函数类型，需显式加上*

	return 0;
}