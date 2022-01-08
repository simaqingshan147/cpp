//强制类型转换
#include<iostream>
using std::cout;
using std::endl;

int main(void)
{
	//static_cast
	//不在乎精度损失
	long double j = 3.14159265357;
	double slope = static_cast<double>(j);

	void* p1 = &j; //void*可以指向任何类型
	//找回存于void*指针中的值
	//warning:转换后的类型必须是指针原来所指的类型
	long double* dp = static_cast<long double*>(p1);

	//const_cast
	//去掉低层const
	const char* cp;
	char* p2 = const_cast<char*>(cp);

	//reinterpret_cast
	int* ip;
	char* pc = reinterpret_cast<char*>(ip);
	//等同于c的类型转换
	char* pc2 = (char*)ip;

	return 0;
}