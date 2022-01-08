//13.3  ---- ��������
#include<iostream>
#include<string>
using namespace std;

//����ඨ�����Լ���swap����,�㷨��ʹ�����Զ���汾
//ֱ�ӵ��ñ�׼��swap�������ܸ��ƴ��󣬻��߽�������

class Ptr {
public:
	//��swap�����������ݳ�Ա
	friend void swap(Ptr&, Ptr&);
	Ptr& operator=(const Ptr);

	//Ĭ�Ϲ��캯��
	Ptr() {
		i = 0;
		ps = new string();
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
		ps = other.ps;
		i = other.i;  
		use = other.use;
		++* use;  //��������
	}

	//��������
	~Ptr() {
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
	}

	void show() const {
		cout << "use= " << *use << endl;
		cout << "ps= " << *ps << endl;
	}

private:
	string* ps;  //��ָ�븴�ƣ�ֻ����ָ��
	int i;
	size_t* use;  //���ü���
};

//swap������Ϊ���Ż�����,��������Ϊinline����
inline
void swap(Ptr& lptr, Ptr& rptr) {
	//ʹ�ñ�׼��swap
	using std::swap;
	swap(lptr.ps, rptr.ps);  //����ָ�룬����string����
	swap(lptr.use, rptr.use);
	swap(lptr.i, rptr.i);
}

//��swap���帳ֵ�����
//����������,���������Ҳ����ĸ������н���
//�Զ������Լ���ֵ�Լ����������Ȼ��ȫ
//ע���ββ������ã�ֻ�Ǹ���
Ptr& Ptr::operator=(Ptr other) {
	swap(*this, other);
	return *this;
}

int main()
{
	Ptr test("hello");
	Ptr test2;
	test2 = test;
	test2.show();

	return 0;
}