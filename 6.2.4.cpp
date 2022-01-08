//数组形参
#include<iostream>
using std::cout;
using std::endl;

/*
* void print(const int*);
* void print(const int[]);
* void print(const int[10]);
* 三个等价
* 实际传递的是指向数组首元素的指针
*/

//使用标记指定数组长度
void print1(const char* cp)
{
	if (cp)
	{
		// \0标记数组结束
		while (*cp)
			cout << *cp++;
		cout << endl;
	}
}

//使用标准库规范，即指定首元素和尾后元素的指针
void print2(const int* beg, const int* end)
{
	//输出所有元素，不包含end
	while (beg != end)
		cout << *beg++ << ' ';
	cout << endl;
}

//显示传递一个表示数组大小的形参
void print3(const int ia[], size_t size)
{
	for (size_t i = 0; i != size; ++i)
		cout << ia[i] << ' ';
	cout << endl;
}