//10.4.1 ---- 插入迭代器
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<list>

using namespace std;

vector<int> vi = { 1,2,3,4,5,6,7,8,9,10 };
string str = "asdfjl;kfadsgj;lsdfkgjs;ldfgkj";
list<int> li = { 1,2,3,4,5,6,7,8,9,10 };

//插入迭代器，绑定一个容器，实现对容器添加元素
//利用容器操作给容器插入元素

//vector,string不支持push_front,所以没有front_inserter
void front_Inserter()
{
	auto iter = front_inserter(li);
	for (int i = 11; i <= 20; i++)
		iter = i;  //插入i,等同于*iter=i
	for (int i : li)
		cout << i << " ";
	cout << endl;
}

int main()
{
	front_Inserter();
	return 0;
}
