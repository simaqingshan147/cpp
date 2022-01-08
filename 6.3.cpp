//返回类型和return语句
#include<iostream>
#include<cstdlib>
#include<string>
using std::string;

/*
//错误的函数,complier未报错
bool str_subrange(const string& str1, const string& str2)
{
	if (str1.size() == str2.size())
		return str1 == str2;
	auto size = (str1.size() < str2.size())
		? str1.size() : str2.size();
	for (decltype(size) i = 0; i != size; ++i)
	{
		if (str1[i] == str2[i])
			return;  //错误，无返回值
	}
	//错误，循环后无返回值
}
*/

char& get_val(string& s,string::size_type num)
{
	if (num >= 0 && s.size() > num)
		return s[num];
}

//递归计算阶乘
int factorial(int val)
{
	if (val > 1)
		return factorial(val - 1) * val;
	return 1;
}

int main(void)
{
	string s;
	std::getline(std::cin, s);
	get_val(s, 0) = 'A';  //能为返回类型是非常量引用的函数结果赋值
	std::cout << s << std::endl;

	return EXIT_SUCCESS;  //cstdlib
}

