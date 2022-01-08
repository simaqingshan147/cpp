//额外的string操作
#include<iostream>
#include<string>
using namespace std;

//string构造
void knowledge1()
{
	string a;
	a = "string";
	char str[12] = "string";
	str[6] = '\0';

	string b(str, 12);   //复制数组,该数组至少包含12个元素
	string c(a, 0);     //c是a从下标0开始的拷贝
	string d(a, 0, 6);  //从下标0开始拷贝a，拷贝长度为6
	//string e(a, 100, 6);    //下标超过，未定义,抛出out_of_range
	string e(a, 0, 100);     //只拷贝到结尾
}

//substr
void knowledge2()
{
	//substr(beg,length)
	//beg开始字符下标
	//length拷贝几位，超出就只拷贝到结尾

	//substr(n)
	//从下标n开始复制到结尾

	string s("hello world");
	string s2 = s.substr(0, 5);
	string s3 = s.substr(6);
	string s4 = s.substr(12);   //out_of_range
}

int main()
{
	return 0;
}