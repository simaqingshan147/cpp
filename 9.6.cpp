//����������
#include<iostream>
#include<vector>
#include<string>
#include<stack>   //ջ
#include<deque>   //˫�˶���

using namespace std;

//��������ʼ��
void knowledge1()
{
	deque<int> d1;
	//stack��queue����dequeʵ��
	//������deque��ʼ��stack��queue
	stack<int> s1(d1);

	//����������ʱ����������˳��������Ϊ�ڶ������Ͳ���
	//������Ĭ����������
	//��ͬ������������������Ҫ��ͬ
	stack<string, vector<string>> str_stk;
}

//ջ������
void knowledge2()
{
	stack<int> intStack;
	for (size_t ix = 0; ix != 10; ++ix)
		intStack.push(ix);
	while (!intStack.empty())
	{
		int value = intStack.top();    //����ջ��Ԫ�أ�������
		intStack.pop();
	}
}


int main()
{
	return 0;
}
