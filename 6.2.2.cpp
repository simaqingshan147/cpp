//函数的参数传递
#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;

//指针形参
void reset1(int* ip)
{
	*ip = 0;
	ip = 0;
}

//引用形参
void reset2(int& i)
{
	i = 0;
}

//string类型可能很长，使用引用更高效
//无需改变引用实参的值时，声明为常量引用
//比较两string对象的长度
bool isshorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

//返回s中c第一次出现的位置索引(下标）
//引用实参occurs统计c出现的次数
string::size_type find_char(const string& s, char c,
	string::size_type& occurs)
{
	auto ret = s.size();  //第一次出现的位置
	occurs = 0;
	for (decltype(ret) i = 0; i != s.size(); ++i)
	{
		if (s[i] == c)
		{
			if (ret == s.size())
				ret = i;  //只记录第一次出现的位置
			++occurs;
		}
		return ret;
	}
}

int main(void)
{
	//传值调用，对形参的操作不会影响实参
	int n = 0;
	int i = n;
	i = 42; 
	//类似于上面

	//指针形参也是传值调用
	//指针本身的值，即实参值未变
	//改变的是指针指向的值
	reset1(&i);
	cout << "i= " << i << endl;

	//传引用调用，形参是引用类型，对形参的操作影响实参
	//在C中常常用指针实现
	int j = 42;
	reset2(j);
	cout << "j= " << j << endl;

	//传值调用，本质上是拷贝初始化形参
	//实参较大，或不支持拷贝时，使用引用
	//需要函数返回多个值，使用额外的引用实参保存
	//上述功能，在C中用指针实现

	return 0;
}