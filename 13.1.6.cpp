//13.1.6 -- 阻止拷贝
#include<iostream>
#include<string>

using namespace std;


//阻止拷贝
struct Nocopy {
	int a;
	string s;

	Nocopy() = default; //合成默认构造函数
	Nocopy(Nocopy&) = delete;  //阻止拷贝
	Nocopy& operator=(const Nocopy&) = delete;  //阻止赋值

	~Nocopy() = default;
};

//阻止析构
struct Noerase {
	int a;
	string s;

	Noerase() = default; //合成默认构造函数

	~Noerase() = delete;  //阻止析构
};

int main()
{
	Nocopy test;
	test.a = 1; test.s = "hello";

	//Nocopy test2(test);
	//Nocopy test2 = test;

	//禁止析构函数的类无法定义对象
	//Noerase a;

	//但可以动态分配对象
	Noerase* p = new Noerase();
	//但不能删除
	//delete p;

	return 0;
}