//文件输入输出
#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	/*
	//写入文件
	//写入，默认截断，即清空原内容后输入
	ofstream out("test.txt");  //隐式out模式，隐式截断
	ofstream out1("test.txt", ofstream::out);   //隐式截断
	ofstream out2("test.txt", ofstream::out | ofstream::trunc);   //显式截断

	//保留文件内容，必须显式指定app模式
	//app 文件末尾写入
	ofstream out3("test.txt", ofstream::out | ofstream::app);
	*/

	string temp;
	char buf[100];
	char c;
	
	ifstream infile("test.txt",istream::in);  //只读模式
	if (infile.is_open())   //调用open失败,则failbit置位
	{
		//直接读取
		//遇空格停止，无法读取空格
		while (infile >> temp)
			cout << temp << endl;

		infile.clear();                 //重置状态
		infile.seekg(istream::beg);    //回到文件开头
		//逐行读取
		while (infile.getline(buf, sizeof(buf)))
			cout << buf << endl;

		infile.clear();
		infile.seekg(istream::beg);
		//逐字符读取
		while ((c = infile.get()) != EOF)
			cout << c;
		cout << endl;
	}
	else
	{
		cout << "打开失败!" << endl;
		getchar();
	}
	infile.close();

	return 0;
}