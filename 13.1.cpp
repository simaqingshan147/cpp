//13.1 ��Ŀ�������ֵ������
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class foo {
public:
	foo() {
		a = 0;
		s = "";
	}
	foo(const int i, const string& j) {
		a = i; s = j;
	}

	//�������캯��,��һ����������������
	//û�б������ᶨ��һ��
	foo(const foo& other) {
		a = other.a;
		s = other.s;
	}

	//������������������Ǻ���
	//���������ǳ�Ա�������������this
	//��ֵ�����Ӧ��Ĭ�ϸ�ֵ����һ�£����������������
	foo& operator=(const foo& other) {
		a = other.a; s = other.s;
	}

	//���������������ܲ������޷�����
	// û�У��������ϳ�����������������Ϊ��(��������ʲô����ִ��)
	//����ִ�к����壬Ȼ�󰴳�ʼ��˳�����������
	~foo() {
		cout << "bye" << endl;
	}
	//��������������������
	//���ٽ׶��ڹ��캯��������

	int a;
	string s;
};



int main()
{
	foo b(12,"hello");

	//�������ϳɿ�����ֵ�����
	foo a = b;  //������ʼ��
	return 0;
}