//传递可变数量的形参
#include<iostream>
#include<string>
#include<initializer_list>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::initializer_list;

//initializer_list,标准库类型，表示某种特定类型的值的数组
//表内元素都是常量值
void Printall(initializer_list<string> str, int num)
{
	cout << "输出initializer_list中的" << num << "个元素" << endl;
	for (string s : str)
		cout << s << endl;
	cout << "输出完成!" << endl;
}

int main(void)
{
	string a, b, c, d;
	cout << "请输入" << endl;
	getline(cin, a);
	cout << "请输入" << endl;
	getline(cin, b);
	cout << "请输入" << endl;
	getline(cin, c);
	cout << "请输入" << endl;
	getline(cin, d);

	//传递的值的序列必须放在花括号内
	Printall({ a,b,c,d }, 4);

	return 0;
}