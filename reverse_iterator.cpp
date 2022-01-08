//10.4.3  -- ���������
#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>

using namespace std;

vector<int> vec = { 1,2,3,4,5,6,7,8,9,10 };
string line = "FIRST,MIDDLE,LAST";


//�������������forward_list�ⶼ֧��
void fcn1()
{
	auto rbeg = vec.rbegin();  //ָ���һ��Ԫ�ص�ǰһ��
	auto rend = vec.rend();    //ָ�����һ��Ԫ��

	//++��ǰ��,--�Ǻ���
	while (rend != rbeg)
		cout << *rbeg++;
	cout << endl;
}

void fcn2()
{
	//comma������ָ��������ҵ�һ������
	auto comma = find(line.cbegin(), line.cend(), ',');
	//�����һ������
	cout << string(line.cbegin(), comma) << endl;

	//��ӡ���һ������
	//rcomma������ָ����������һ������,ע�����Ƿ��������
	auto rcomma = find(line.crbegin(), line.crend(), ',');
	cout << string(line.crbegin(), rcomma) << endl;  //�������,����

	//reverse_iterator::base()��ת��Ϊ��ͨ������
	cout << string(rcomma.base(), line.cend()) << endl;

	//warning��Ϊ�˱�֤��ͬ����պ�����,rcomma.base()����,ָ��'L'��������','
	//ͬ���ĵ���,begin()�����rend()Ҳ��������һλ
}

int main()
{
	fcn1();
	fcn2();
	return 0;
}
