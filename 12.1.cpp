//12.1 ---- 动态内存与智能指针
#include<iostream>
#include<string>
#include<memory>
using namespace std;

//智能指针模板
void fcn1()
{
	//shared_ptr类
	shared_ptr<string> p1;  //空指针
	if (p1&&p1->empty())  //解引用string的empty
		*p1 = "string";  //解引用，赋值
	

	//安全的分配和使用动态内存
	//make_shared函数括号中的参数必须能初始化给定对象

	//int *iptr = new int(42) iptr是指向42的指针
	shared_ptr<int> iptr = make_shared<int>(42);
	//string* sptr = new string*("9999999999")
	shared_ptr<string> sptr = make_shared<string>(10, '9');

	//shared_str拷贝赋值
	//shared_str每被拷贝一次，指向对象引用计数加一
	//shared_str被赋予新值或销毁,指向对象引用计数减一
	cout << "iptr引用次数为" << iptr.use_count() << endl;  //1
	auto q(iptr);
	cout << "iptr引用次数为" << iptr.use_count() << endl;  //2
	cout << "q的引用次数为" << q.use_count() << endl;    //2
}

int main()
{
	fcn1();
	return 0;
}