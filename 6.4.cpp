//函数重载
#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

string read();
void print(const string&);
void print(double);  //重载print函数
void fooBar(int ival)
{
	bool read = false;
	//string = read(); 错误,read是布尔值
	void print(int);
	//print("value:"); 错误,外面的print被覆盖
}

string read()
{
	return "ha!";
}
