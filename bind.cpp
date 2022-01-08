//10.3.4 ������
//bind���� ͨ�ú���������
#include<iostream>
#include<algorithm>
#include<functional>  //bind����,placeholders�����ռ�,ref����
#include<vector>
#include<string>

using namespace std;

bool isShorter(const string& a, const string& b){ return a.size() < b.size(); }
bool check_size(const string& s, int size) { return s.size() > size; }

void fcn1()
{
	//�в��������lambda�����ױ���������
	//��Ϊ�����㷨�Լ�Ԫν��������
	//�������в����ж���βδ��ݲ������

	/*
	bind����
	auto newfun = bind(fun,arg_list);
	newfun��fun���ǿɵ��ö���
	arg_list�����б�
	����newfun���൱�ڵ���fun(arg_list)
	*/

	//_n:ռλ��,��ʾ�����º����Ĳ���
	// _n��ʾ���º����ĵ�n������
	// ռλ���ĸ������º����Ĳ�������
	

	//check(_1) = check(_1,6)
	auto check6 = bind(check_size, placeholders::_1, 6);
	string s = "hello!";
	cout << check6(s) << endl;
}

int main()
{
	vector<string> words;
	string temp;
	int sz = 5;

	cout << "�������ַ���(����λ������q��ֹ):" << endl;
	while (cin >> temp && temp.find("q") == string::npos)
	{
		words.push_back(temp);
		cout << "�������ַ���(����λ������q��ֹ):" << endl;
	}

	//����������words
	stable_sort(words.begin(), words.end(), isShorter);

	/*
	* lambdaʵ��
	auto wc = find_if(words.begin(), words.end(),
		[sz](const string& a)
		{return a.size() >= sz; });
	*/

	//bindʵ��
	auto wc = find_if(words.begin(), words.end(),
		bind(check_size, placeholders::_1, sz));

	size_t count = words.end() - wc;
	cout << count << " " << (count == 1 ? "word" : "words")
		<< " of length " << sz << " or longer" << endl;

	for_each(wc, words.end(),
		[](const string& s) {cout << s << " "; });
	cout << endl;

	return 0;
}

//bind�Ĳ���ӳ��
int myf(int a, int b, int c, int d, int e) { return a; }

void fcn2()
{
	int a = 10; int b = 10; int c = 10;
	//g(_1,_2) = myf(a,b,_2,c,_1)
	auto g = bind(myf, a, b, placeholders::_2, c, placeholders::_1);

	//bind�в���ռλ���Ĳ���Ĭ�Ͽ���
	//���ܿ����Ĳ���,ʹ�ñ�׼��ref

	//��������ܿ�����ֻ������
	auto myprint = bind(fprintf, ref(cout), placeholders::_1);
}