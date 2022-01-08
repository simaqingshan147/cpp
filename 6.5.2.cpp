#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

//���庯��Ϊ��������
inline const string& shorterString
	(const string& s1, const string& s2)
{
	return s1.size() <= s2.size() ? s1 : s2;
}

//���庯��Ϊconstexpr����
//��ʽָ��Ϊ��������

//constexprֻ����һ��return���
//�������ͣ������β����ͱ���������ֵ
constexpr int new_sz() { return 42; }

//�ɰ���������䣬��Щ���������ʱ��ִ���κβ���
constexpr size_t scale(size_t cnt)
{
	return new_sz() * cnt;
}

int main()
{
	string s1, s2;
	s1 = "hhhhhhhhhhhh";
	s2 = "asdkjffl;gh";
	cout << shorterString(s1, s2) << endl;
	/*
	����������չ��
	�ȼ���
	cout<<(s1.size() <= s2.size() ? s1 : s2)<<endl;
	�������������п���
	*/
	
	int i = scale(42);
	cout << i << endl;

	return 0;
}