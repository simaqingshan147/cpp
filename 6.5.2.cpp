#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//定义函数为内联函数
inline const string& shorterString
	(const string& s1, const string& s2)
{
	return s1.size() <= s2.size() ? s1 : s2;
}

//定义函数为constexpr函数
//隐式指定为内联函数

//constexpr只能有一条return语句
//返回类型，所有形参类型必须是字面值
constexpr int new_sz() { return 42; }

//可包含其他语句，这些语句在运行时不执行任何操作
constexpr size_t scale(size_t cnt)
{
	return new_sz() * cnt;
}

int main()
{
	string s1, s2;
	s1 = "hhhhhhhhhhhh";
	s2 = "asdkjffl;gh";
	cout << shorterString(s1, s2) << endl;
	/*
	将函数内联展开
	等价于
	cout<<(s1.size() <= s2.size() ? s1 : s2)<<endl;
	消除函数的运行开销
	*/
	
	int i = scale(42);
	cout << i << endl;

	return 0;
}