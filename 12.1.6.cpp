//12.1.6  ---- weak_ptr
#include<iostream>
#include<string>
#include<memory>
using namespace std;

int main()
{
	//weak指向由shared_ptr管理的对象
	shared_ptr<string> s(new string("hello"));
	cout << s.use_count() << endl;
	//用智能指针初始化
	weak_ptr<string> ws(s);
	cout << s.use_count() << endl;   //绑定weak不增加引用计数

	//lock，如果指向的对象引用计数为0，返回空shared_ptr
	//否则返回指向它对象的shared_ptr

	//检查weak管理的内存是否释放,然后初始化s2
	if (shared_ptr<string> s2 = ws.lock())
		cout << *s2 << endl;

}