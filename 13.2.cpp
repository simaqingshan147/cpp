//13.2 ---- �������ƺ���Դ����
#include<iostream>
#include<string>
using namespace std;

//��ֵ����,ÿ�����ֵ���Լ��ĸ���
//��ָ�뿽��,ÿ���๲��ײ���󣬸ı丱��Ҳ�ı�Դ����

//��Ϊ��ֵ����
class a {
public:
	int num;
	//�˻�������Ϊÿ��ָ��ָ��ͬ��string,��strΪ��ֵ����
	string* str;	

	a() {
		num = 0;
		str = new string();
	}

	~a() {
		delete str;
	}

	//�������캯��,ֱ�ӿ���ֵ
	a(const a& other) {
		num = other.num;

		//*str = *other.str;
		//���󣬲���ɵ����Աָ��ͬһ�ڴ�
		//delete str�Ͱ���һ��Ҳdelete��

		auto newp = new string(*other.str);
		delete str;
		str = newp;
	}

	//������ֵ������������������͹��캯���Ĳ���
	//������������Դ�����Ҳ���󿽱�����
	//һ��Ҫ����ȷ��˳��,Ҫ�������Լ������Լ�Ҳ����������
	a& operator=(const a& other) {
		//�����Ҳ�����
		//��������ֱ��ɾ���ٸ�ֵ�����븳���Լ���������
		auto newp = new string(*other.str);

		//�ͷž��ڴ�
		delete str;
		//���������
		num = other.num;
		str = newp;
		
		//���ر�����
		return *this;
	}
};

//��Ϊ��ָ�����
//ֱ�ӹ�����Դ�����Զ������ü���
//���ü���Ӧ�����ڶ�̬�ڴ��У������޸ļ�������ȫ���޸�
class Ptr {
public:
	//Ĭ�Ϲ��캯��
	Ptr() {
		i = 0;
		ps = new string();    //Ĭ��Ϊ���ַ���
		//��������ʼ��Ϊ1����Ϊ���ַ���Ҳ���Ա�����
		use = new size_t(1);
	}

	//ָ��str�Ĺ��캯��
	Ptr(const string& s) {
		//����ֱ��*ps = s,s������
		ps = new string(s);
		i = 0;
		use = new size_t(1); //��������ʼ��Ϊ1
	}
	
	//�������캯��
	Ptr(const Ptr& other) {
		//����ָ�룬ָ����ͬ�ڴ�
		ps = other.ps;
		i = other.i;  //�����ֵ����

		//��������һ�𿽱���ָ����ͬ������
		//����ǿ�����ʼ����û��ԭ������
		use = other.use;
		++*use;  //��������
	}

	//������ֵ�����
	//�����Լ������Լ���������ȵ�����ݼ�����������
	Ptr& operator=(const Ptr& other) {
		//�����Ҳ࿽������
		++* other.use;
		//�ݼ�ԭ����
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
		//����
		ps = other.ps;
		i = other.i;
		use = other.use;
		return *this;  //���ر�����
	}

	//��������
	~Ptr() {

		//ֻ�ܵݼ����ü���
		//���ü���Ϊ0ʱ��������
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
	}

	//��ʾ
	void show() const {
		cout << "use= " << *use << endl;
		cout << "ps= " << *ps << endl;
	}

private:
	string* ps;  //��ָ�븴�ƣ�ֻ����ָ��
	int i;
	size_t* use;  //���ü���
};

int main()
{
	
	a test;
	test.num = 1;
	*test.str = "hello";
	a test2(test);
	cout << test2.num<<" " << *test2.str << endl;
	

	Ptr p1("hello");
	//������ʼ��
	Ptr p2(p1);
	cout << "p1: "; p1.show();
	cout << "p2: "; p2.show();
	//���ҿ���
	p1 = p1;
	cout << "p1: "; p1.show();

	return 0;
}