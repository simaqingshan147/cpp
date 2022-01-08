//12.1.5 ---- unique_ptr
#include<iostream>
#include<string>
#include<memory>
using namespace std;

//unique_ptr 独占指向对象
//该指针销毁，指向内存也销毁

void fcn1()
{
	//*ptr = 42;
	unique_ptr<int> uptr(new int(42));
	unique_ptr<int> uptr2(new int(42));
	unique_ptr<int> uptr3(new int(42));
	unique_ptr<int> uptr4(new int(42));

	//因为独占对象，所以不支持拷贝或赋值
	//unique_ptr<int> p3(uptr);  不能拷贝
	//unique_ptr<int> p3 = uptr;  不能赋值

	uptr = nullptr;  //释放对象,uptr为空
	int* ptr = uptr2.release();  //uptr2放弃控制权,返回普通指针，置空
	uptr3.reset();  //释放对象
	uptr3.reset(ptr);  //释放原对象，指向ptr

	//所有权转移
	unique_ptr<string> ptrs1(new string("hello"));
	unique_ptr<string> ptrs2(ptrs1.release());  //转移给ptrs2

	unique_ptr<string> ptrs3(new string("hello"));
	ptrs3.reset(ptrs2.release());  //转移给ptrs3
}

void fcn2()
{
	shared_ptr<int> p1 = make_shared<int>(42);
	shared_ptr<int> p2(p1);
	shared_ptr<int> p3(p2);

	cout << "p1: " << p1.use_count() << endl;
	cout << "p2: " << p2.use_count() << endl;
	cout << "p3: " << p3.use_count() << endl;
	p3.reset();
	cout << "p1: " << p1.use_count() << endl;
	cout << "p2: " << p2.use_count() << endl;
	cout << "p3: " << p3.use_count() << endl;

}

int main()
{

	return 0;
}