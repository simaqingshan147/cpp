//����string�����е��ַ�
#include<iostream>
#include<cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;

//����s�еı�������
void PunchNum(string s)
{
	//punct_cnt������Ϊstring::size_type
	decltype(s.size()) punct_cnt = 0;
	for (auto c : s)
	{
		if (std::ispunct(c))
			++punct_cnt;
	}
	cout << punct_cnt
		<< " punctuation chracters in " << s << endl;
}

//��sת��Ϊ��д
void AllUpper(string s)
{
	//c�����ã���˸�ֵ��佫�ı�s���ַ���ֵs
	for (auto& c : s)
		c = std::toupper(c);
	cout << s << endl;
}

int main()
{
	
	//ÿ�����һ���ַ�
	string str("some,string");
	/*
	//��Χfor���
	for (auto c : str)  //c��char����
		cout << c << endl;
	*/
	//PunchNum(str);
	AllUpper(str);
	return 0;
}