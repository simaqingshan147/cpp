//iostream迭代器
#include<iostream>
#include<iterator>
#include<numeric>
#include<vector>

using namespace std;

//输入流迭代器基本操作
void fcn1()
{
	istream_iterator<int> it(cin);  //从cin读取int
	istream_iterator<int> eof;      //默认初始化迭代器当作尾后迭代器
	vector<int> vec;

	//ctrl+z视为终止符
	while (it != eof)
		vec.push_back(*it++);
	//解引用，添加旧值，递增

	cout << "vec: ";
	for (int i : vec)
		cout << i << " ";
	cout << endl;
}

//使用算法操作流迭代器
void sum()
{
	//计算标准输入读取值的和
	istream_iterator<int> in(cin), eof;
	cout << accumulate(in, eof, 0) << endl;
}

//输出流迭代器基本操作
void fcn2()
{
	//将类型为int的值写入cout中,每个值后跟一个空格
	//第二个参数必须是C风格字符串
	ostream_iterator<int> iter(cout, " ");
	vector<int>vec = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i : vec)
		*iter++ = i;
	cout << endl;
	//递增，返回旧值写入i
	//ostream_iterator可以省略解引用和递增运算符
	//即iter=i;
}

int main()
{
	fcn2();
	return 0;
}