//泛型算法概述
#include<iostream>
#include<vector>
#include<algorithm>   //操作容器，但独立于容器
#include<numeric>     //数值泛型算法

using namespace std;

int main()
{
	int val = 42;
	vector<int> vec;
	for (int i = 0; i < 101; i++)
		vec.push_back(i);

	//find算法返回对应值的迭代器
	///返回cend(),表示没找到
	auto result = find(vec.begin(), vec.end(), val);
	cout << "The value " << val
		<< (result == vec.cend()
			? " is not present" : "is present") << endl;
	//任何有迭代器的容器都可以find

	//数组也可以find by指针
	int ia[] = { 27,210,12,47,109,83 };
	int val2 = 83;
	int* res = find(begin(ia), end(ia), val2);
	cout << "res = " << res - ia << endl;

	//范围
	auto res2 = find(ia + 1, ia + 4, val);
	cout << "res2 = " << res2 - ia << endl;
	//查找1,2,3，类似于尾后迭代器
	//失败返回ia+4,即该范围的"end"

	return 0;
}