//���ݿɱ��������β�
#include<iostream>
#include<string>
#include<initializer_list>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::initializer_list;

//initializer_list,��׼�����ͣ���ʾĳ���ض����͵�ֵ������
//����Ԫ�ض��ǳ���ֵ
void Printall(initializer_list<string> str, int num)
{
	cout << "���initializer_list�е�" << num << "��Ԫ��" << endl;
	for (string s : str)
		cout << s << endl;
	cout << "������!" << endl;
}

int main(void)
{
	string a, b, c, d;
	cout << "������" << endl;
	getline(cin, a);
	cout << "������" << endl;
	getline(cin, b);
	cout << "������" << endl;
	getline(cin, c);
	cout << "������" << endl;
	getline(cin, d);

	//���ݵ�ֵ�����б�����ڻ�������
	Printall({ a,b,c,d }, 4);

	return 0;
}