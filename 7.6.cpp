//��ľ�̬��Ա
//��ʱ����ҪһЩ��Ա���౾����أ�������������������
#include<iostream>
#include<string>
using std::string;

//�����˻���¼��
class Account {
public:
	void calculate() { amount += amount * interestRate; }
	static double rate() { return interestRate; }
	static void rate(double);
private:
	string owner;
	double amount;
	static double interestRate;    //����
	static constexpr int period = 30;  //constexper��̬��Ա�������ڳ�ʼ��
	static double initRate();
};

//���ⶨ�徲̬��Ա
void Account::rate(double newRate)
{
	//���ⶨ�徲̬��Ա,�����ظ�static�ؼ���
	interestRate = newRate;
}

int main()
{
	//����account�����о�̬��Ա
	double r;
	r = Account::rate();   //ʹ����������������ʾ�̬��Ա
	
	Account ac1;
	Account* ac2 = &ac1;
	r = ac1.rate();
	r = ac2->rate();
}

//��Ϊstatic��Ա�������κζ���

class Bar {
	//static��Ա�����ǲ���ȫ����,�������������
	static Bar men1;
	Bar* men2;   //ָ������ǲ���ȫ����
	//Bar men3;   ���ݳ�Ա��������������
};

class C {
public:
	int a;
	static int b;
	//����ʹ�þ�̬��Ա��ΪĬ��ʵ��
	int function(int d = b) { return d; }
};