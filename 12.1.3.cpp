//12.1.3 shared_ptr和new结合使用
#include<iostream>
#include<memory>
using namespace std;

void fcn1()
{
	//用new返回的指针初始化智能指针
	shared_ptr<int> i(new int(42));

	//接受指针参数的智能指针构造函数是explicit的
	//即必须使用直接初始化来初始化智能指针
	//shared_ptr<int> i2 = new int(42);   错误,隐式转换

	int num = 42;
	int* p2 = &num;
	
	//默认绑定动态内存到智能指针
	//因为智能指针用delete释放关联对象
	shared_ptr<int> i2(p2);  //delete非动态内存，未定义
}

void process(shared_ptr<int> ptr) { cout << *ptr << endl; }

//不要混合使用普通指针和智能指针
void fcn2()
{
	shared_ptr<int> p(new int(42));  //*p = 42

	//正确
	//p复制给形参，引用计数加一,离开函数销毁形参，引用次数为1
	process(p);
	cout << p.use_count() << endl;   //1

	int* x(new int(1024));  //普通指针

	//process(x) 错误,不能隐式转换int*为智能指针

	//合法,但x内存被释放
	//p = shared<int>(x)，引用次数为1
	//离开函数p销毁，引用次数为0，自动释放x指向的内存
	process(shared_ptr<int>(x));
	//cout << *x << endl; 内存被释放!!!
}

//其他shared_ptr操作
void fcn3()
{
	shared_ptr<int> p(new int(10));  //*p = 10;

	//reset，更新引用计数,更新指针指向对象
	//如果原引用计数为0，销毁原指向对象

	p.reset(new int(1024));  //10被销毁

	//改变底层对象前，检查自己是否是唯一指向的指针
	if (!p.unique())
		p.reset(new int(*p));
	//将原值拷贝出来，则p的更新不会影响其他指向1024的指针
	*p += 1024;  //更新对象值
}