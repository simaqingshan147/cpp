//10.4.1 ---- ���������
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<list>

using namespace std;

vector<int> vi = { 1,2,3,4,5,6,7,8,9,10 };
string str = "asdfjl;kfadsgj;lsdfkgjs;ldfgkj";
list<int> li = { 1,2,3,4,5,6,7,8,9,10 };

//�������������һ��������ʵ�ֶ��������Ԫ��
//����������������������Ԫ��

//vector,string��֧��push_front,����û��front_inserter
void front_Inserter()
{
	auto iter = front_inserter(li);
	for (int i = 11; i <= 20; i++)
		iter = i;  //����i,��ͬ��*iter=i
	for (int i : li)
		cout << i << " ";
	cout << endl;
}

int main()
{
	front_Inserter();
	return 0;
}
