//10.4.3  -- 反向迭代器
#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

using namespace std;

vector<int> vec = { 1,2,3,4,5,6,7,8,9,10 };
string line = "FIRST,MIDDLE,LAST";


//反向迭代器，除forward_list外都支持
void fcn1()
{
	auto rbeg = vec.rbegin();  //指向第一个元素的前一个
	auto rend = vec.rend();    //指向最后一个元素

	//++是前移,--是后移
	while (rend != rbeg)
		cout << *rbeg++;
	cout << endl;
}

void fcn2()
{
	//comma迭代器指向从左往右第一个逗号
	auto comma = find(line.cbegin(), line.cend(), ',');
	//输出第一个单词
	cout << string(line.cbegin(), comma) << endl;

	//打印最后一个单词
	//rcomma迭代器指向从右往左第一个逗号,注意它是反向迭代器
	auto rcomma = find(line.crbegin(), line.crend(), ',');
	cout << string(line.crbegin(), rcomma) << endl;  //反向输出,错误

	//reverse_iterator::base()：转换为普通迭代器
	cout << string(rcomma.base(), line.cend()) << endl;

	//warning：为了保证相同的左闭合区间,rcomma.base()右移,指向'L'，而不是','
	//同样的道理,begin()相对与rend()也是右移了一位
}

int main()
{
	fcn1();
	fcn2();
	return 0;
}
