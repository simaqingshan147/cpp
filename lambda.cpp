//10.3.2 lambda���ʽ
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

void fcn1(void);
void fcn2(void);
void fcn3(void);
void fcn4(void);

//lambda���ʽ���ɵ��ö���,�������Ϊһ��δ��������������
//[�����б�] (�����б�) -> �������� {������}
//capture list��lambda�����ж���ľֲ������б�
//����ʹ��β�÷���

void lambda()
{
	//��f����Ϊһ���ɵ��ö���
	//���������൱��ָ���ղ����б�
	//���Է������ͣ����ݴ����ƶϳ���
	auto f = [] {return 42; };

	auto e = [](int a, int b)->int {if (a > b)return a; return b; };

	//ʹ�õ��������()����lambda
	cout << f() << endl;
	cout << e(1, 2) << endl;
}

bool isShorter(const string& a, const string& b)
{
	return a.size() < b.size();
}

int main()
{
	vector<string> words;
	string temp;
	int sz = 5;
	//find_if�㷨,���ص�һ��ʹν�ʷ��ط�0ֵ��Ԫ��
	//find_ifֻ����һԪν��

	cout << "�������ַ���(����λ������q��ֹ):" << endl;
	while (cin >> temp && temp.find("q") == string::npos)
	{
		words.push_back(temp);
		cout << "�������ַ���(����λ������q��ֹ):" << endl;
	}

	//����������words
	stable_sort(words.begin(), words.end(), isShorter);

	//��һ�����ȴ���5���ַ���
	//��lambda��ΪһԪν��
	auto wc = find_if(words.begin(), words.end(),
		[sz](const string& a)
		{return a.size() >= sz; });

	size_t count = words.end() - wc;
	cout << count << " " << (count == 1 ? "word" : "words")
		<< " of length " << sz << " or longer" << endl;

	//for_each�㷨
	//�Է�Χ�ڵ�ÿ��Ԫ�أ�ִ��ν��

	//��ӡ���ȴ���sz�������ַ���
	for_each(wc, words.end(),
		[](const string& s) {cout << s << " "; });
	cout << endl;
	
	return 0;
}

//lambda�����뷵��

//��������
void fcn1()
{
	size_t v1 = 42;  //�ֲ�����
	auto f = [v1]{ return v1; };
	v1 = 0;
	auto j = f();  //jΪ42������0
	//�����б��v1�ǿ�����ʼ����
}

//���ò���
//warning��ʹ�����ò��񣬱��뱣֤����ִ��ʱ���ñ�������
void fcn2()
{
	size_t v1 = 42;  //�ֲ�����
	auto f = [v1] { return v1; };
	v1 = 0;
	auto j = f();  //j=0
}

//��ʽ����
void fcn3()
{
	int a = 10; int b = 20;

	auto f1 = [=] {return a; };  //�Զ���������a
	auto f2 = [&] {return b; };  //�Զ����ò���b

	//���ʹ����ʽ�������ʽ����
	//=��&�����ǵ�һ��Ԫ��
	//��ʽ����ʽ������벻ͬ
	auto f3 = [=, &b] {if (a > b)return a; return b; };
	auto f4 = [&, b] {if (a > b)return a; return b; };
	a = 20; b = 0;
	cout << f1() << endl;  //10
	cout << f2() << endl;  //0
	cout << f3() << endl;  //10
	cout << f4() << endl;  //20
}

//�ɱ�lambda
void fcn4(void)
{
	//�ı䱻���������ֵ���ӹؼ���mutable
	size_t v1 = 42;
	auto f = [v1]()mutable {return ++v1; };
	v1 = 0;
	auto j = f();  //43
}

//Ϊlambdaָ����������
void fcn5()
{
	//���lambda����return���֮����������,�������ٶ�����void
	vector<int> vi(1, 10);
	/*
	����,���Ͳ�ƥ�䣬�޷����غ���
	transform(vi.begin(),vi.end(),vi.begin(),
		[](int i) {if (i < 0) return -1 * i; else return i; });
	*/
	transform(vi.begin(), vi.end(),vi.begin(),
		[](int i)->int{if (i < 0) return -1 * i; else return i; });
}