//容器适配器
#include<iostream>
#include<vector>
#include<string>
#include<stack>   //栈
#include<deque>   //双端队列

using namespace std;

//适配器初始化
void knowledge1()
{
	deque<int> d1;
	//stack和queue基于deque实现
	//可以用deque初始化stack和queue
	stack<int> s1(d1);

	//创建适配器时，将命名的顺序容器作为第二个类型参数
	//来重载默认容器类型
	//不同的适配器，对容器的要求不同
	stack<string, vector<string>> str_stk;
}

//栈适配器
void knowledge2()
{
	stack<int> intStack;
	for (size_t ix = 0; ix != 10; ++ix)
		intStack.push(ix);
	while (!intStack.empty())
	{
		int value = intStack.top();    //返回栈顶元素，不弹出
		intStack.pop();
	}
}


int main()
{
	return 0;
}
