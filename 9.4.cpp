//9.4 vvector�����������
#include<iostream>
#include<vector>
#include<string>
#include<deque>
//��̬�����洢
using namespace std;

//����vector��string,����ʵ����͸���ӿ���
//���ڴ���䲿�ֻ���
void knowledge1()
{
	vector<int> ivec(10, 100);
	string str = "string";
	deque<int> ide(10, 100);

	//shrink_to_fit,������capacity��С��size
	//����ʵ�ֿɺ��Դ�����,����һ������
	//ֻ������vector,string,deque
	ivec.shrink_to_fit();
	str.shrink_to_fit();
	ide.shrink_to_fit();

	//capacity����ʾ����
	//ֻ������vector,string
	ivec.capacity();
	str.capacity();

	//reserve,�����ڴ�ռ�
	//��������С�ڵ�ǰ����������
	//ֻ������vector,string
	ivec.reserve(1);   //����
	ivec.reserve(100);  //ִ��
	str.reserve(100);

	ivec.clear();
	cout << " ivec: size" << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	//����24��Ԫ��
	for (vector<int>::size_type ix = 0; ix != 24; ++ix)
		ivec.push_back(ix);

	//size=24,capacity>24
	cout << "ivec.size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	//���н��:size=24,capacity=28
}

int main()
{

	return 0;
}