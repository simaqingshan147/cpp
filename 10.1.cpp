//�����㷨����
#include<iostream>
#include<vector>
#include<algorithm>   //����������������������
#include<numeric>     //��ֵ�����㷨

using namespace std;

int main()
{
	int val = 42;
	vector<int> vec;
	for (int i = 0; i < 101; i++)
		vec.push_back(i);

	//find�㷨���ض�Ӧֵ�ĵ�����
	///����cend(),��ʾû�ҵ�
	auto result = find(vec.begin(), vec.end(), val);
	cout << "The value " << val
		<< (result == vec.cend()
			? " is not present" : "is present") << endl;
	//�κ��е�����������������find

	//����Ҳ����find byָ��
	int ia[] = { 27,210,12,47,109,83 };
	int val2 = 83;
	int* res = find(begin(ia), end(ia), val2);
	cout << "res = " << res - ia << endl;

	//��Χ
	auto res2 = find(ia + 1, ia + 4, val);
	cout << "res2 = " << res2 - ia << endl;
	//����1,2,3��������β�������
	//ʧ�ܷ���ia+4,���÷�Χ��"end"

	return 0;
}