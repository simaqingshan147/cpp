//iostream������
#include<iostream>
#include<iterator>
#include<numeric>
#include<vector>

using namespace std;

//��������������������
void fcn1()
{
	istream_iterator<int> it(cin);  //��cin��ȡint
	istream_iterator<int> eof;      //Ĭ�ϳ�ʼ������������β�������
	vector<int> vec;

	//ctrl+z��Ϊ��ֹ��
	while (it != eof)
		vec.push_back(*it++);
	//�����ã���Ӿ�ֵ������

	cout << "vec: ";
	for (int i : vec)
		cout << i << " ";
	cout << endl;
}

//ʹ���㷨������������
void sum()
{
	//�����׼�����ȡֵ�ĺ�
	istream_iterator<int> in(cin), eof;
	cout << accumulate(in, eof, 0) << endl;
}

//�������������������
void fcn2()
{
	//������Ϊint��ֵд��cout��,ÿ��ֵ���һ���ո�
	//�ڶ�������������C����ַ���
	ostream_iterator<int> iter(cout, " ");
	vector<int>vec = { 1,2,3,4,5,6,7,8,9,10 };
	for (int i : vec)
		*iter++ = i;
	cout << endl;
	//���������ؾ�ֵд��i
	//ostream_iterator����ʡ�Խ����ú͵��������
	//��iter=i;
}

int main()
{
	fcn2();
	return 0;
}