//���������
#include<iostream>
#include<string>
using std::string;

typedef double Money;
string bal;

class Account {
public:
	//������������в�����
	//���ڶ��������������Ѱ��
	Money balance() { return bal; }
	//return Money bal
	//��Ϊ�����ȱ����Ա����
	//Ȼ����뺯����
	//������ʹ�����ж�����κ�����
private:
	//typedef char Money;  ����Ӧ�������࿪ʼ��
	Money bal;
};