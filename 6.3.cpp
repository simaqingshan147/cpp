//�������ͺ�return���
#include<iostream>
#include<cstdlib>
#include<string>
using std::string;

/*
//����ĺ���,complierδ����
bool str_subrange(const string& str1, const string& str2)
{
	if (str1.size() == str2.size())
		return str1 == str2;
	auto size = (str1.size() < str2.size())
		? str1.size() : str2.size();
	for (decltype(size) i = 0; i != size; ++i)
	{
		if (str1[i] == str2[i])
			return;  //�����޷���ֵ
	}
	//����ѭ�����޷���ֵ
}
*/

char& get_val(string& s,string::size_type num)
{
	if (num >= 0 && s.size() > num)
		return s[num];
}

//�ݹ����׳�
int factorial(int val)
{
	if (val > 1)
		return factorial(val - 1) * val;
	return 1;
}

int main(void)
{
	string s;
	std::getline(std::cin, s);
	get_val(s, 0) = 'A';  //��Ϊ���������Ƿǳ������õĺ��������ֵ
	std::cout << s << std::endl;

	return EXIT_SUCCESS;  //cstdlib
}

