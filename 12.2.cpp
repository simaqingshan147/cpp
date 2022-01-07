//动态数组
#include<iostream>
#include<new>
#include<memory>  //allocator
#include<vector>
using namespace std;

void fcn1()
{
	int* p = new int[42]();  //返回数组,42个值初始化为0

	//管理动态数组的智能指针
	unique_ptr<int[]> up(p);

	//指向数组时，使用下标
	for (int i = 0; i < 42; i++)
		cout << up[i] << " ";
	cout << endl;
	up.release();  //相当于调用delete[]

	//shared_ptr不直接支持管理动态数组
	//必须定义删除器
	//因为默认情况shared_ptr用delete销毁

	//即，凡是不能用delete直接销毁的都要定义删除器

	//用lambda定义删除器
	shared_ptr<int> sp(p, [](int* p) {delete[] p; });
}

//allocator类
//将内存分配与构造对象分离
void fcn2()
{
	allocator<string> alloc;  
	auto const p = alloc.allocate(10);  //分配10个未构造的string
	auto q = p;
	//cout << *q << endl; 未定义:使用了未构造对象的内存

	alloc.construct(q++);  //*q为空字符串
	alloc.construct(q++, 10, 'c');  //*q = ccccccccccc
	alloc.construct(q++, "hi");

	//q之前才是构造的元素
	while (q != p)
		alloc.destroy(--q);  //释放构造的string

	//q还可以重新使用
	//或者归还内存给系统
	alloc.deallocate(p, 10);
	//指针必须指向分配内存，大小必须与分配时相同
}

//拷贝，填充未初始化内存的算法
//内存未初始化，不能直接拷贝
void fcn3()
{
	vector<int> vi = { 1,2,3,4,5,6,7,8,9,10 };
	
	allocator<int> alloc;
	auto p = alloc.allocate(vi.size() * 2);  //两倍大的动态内存

	//拷贝vi进未初始化内存，返回指向最后一个数之后的内存的指针
	auto q = uninitialized_copy(vi.begin(), vi.end(), p);
	//剩余内存初始化为42
	//指针，赋值元素数量，赋值数
	uninitialized_fill_n(q, vi.size(), 42);
}