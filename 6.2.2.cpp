//�����Ĳ�������
#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;

//ָ���β�
void reset1(int* ip)
{
	*ip = 0;
	ip = 0;
}

//�����β�
void reset2(int& i)
{
	i = 0;
}

//string���Ϳ��ܺܳ���ʹ�����ø���Ч
//����ı�����ʵ�ε�ֵʱ������Ϊ��������
//�Ƚ���string����ĳ���
bool isshorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

//����s��c��һ�γ��ֵ�λ������(�±꣩
//����ʵ��occursͳ��c���ֵĴ���
string::size_type find_char(const string& s, char c,
	string::size_type& occurs)
{
	auto ret = s.size();  //��һ�γ��ֵ�λ��
	occurs = 0;
	for (decltype(ret) i = 0; i != s.size(); ++i)
	{
		if (s[i] == c)
		{
			if (ret == s.size())
				ret = i;  //ֻ��¼��һ�γ��ֵ�λ��
			++occurs;
		}
		return ret;
	}
}

int main(void)
{
	//��ֵ���ã����βεĲ�������Ӱ��ʵ��
	int n = 0;
	int i = n;
	i = 42; 
	//����������

	//ָ���β�Ҳ�Ǵ�ֵ����
	//ָ�뱾���ֵ����ʵ��ֵδ��
	//�ı����ָ��ָ���ֵ
	reset1(&i);
	cout << "i= " << i << endl;

	//�����õ��ã��β����������ͣ����βεĲ���Ӱ��ʵ��
	//��C�г�����ָ��ʵ��
	int j = 42;
	reset2(j);
	cout << "j= " << j << endl;

	//��ֵ���ã��������ǿ�����ʼ���β�
	//ʵ�νϴ󣬻�֧�ֿ���ʱ��ʹ������
	//��Ҫ�������ض��ֵ��ʹ�ö��������ʵ�α���
	//�������ܣ���C����ָ��ʵ��

	return 0;
}