//11.1 ʹ�ù�������
#include<iostream>
#include<map> //map������ؼ�����ͬ��map
#include<set> //set������ؼ�����ͬ��set
#include<unordered_map>  //��ϣ��֯��map
#include<unordered_set>  //��ϣ��֯��set
#include<string>

using namespace std;

//ͳ��ÿ�������������г��ֵĴ���
void fcn1()
{
	//��string,ֵsize_t
	map<string, size_t> word_count;
	string word;
	
	//Ҫ���Եĵ���ͳ�Ƶ�set��
	set<string> exclude = { "The","But","And","Or","An","A",
							"the","but","and","or","an","a" };

	cout << "������:";
	while (cin >> word)
	{
		//ֻͳ�Ʋ���exclude�е�ֵ
		//find���ҵ��˷���Ŀ������������򷵻�β������
		if(exclude.find(word)==exclude.end())
			++word_count[word];  //���ʶ�Ӧ��ֵ��1
		cout << "������:";
	}

	//pairģ������,first��Ա�����,second��Ա����ֵ
	for (const auto& w : word_count)
		cout << w.first << " occurs " << w.second
		<< ((w.second > 1) ? " times" : " time") << endl;
}

//ֵ��ʼ����������
void fcn2()
{
	//��-ֵ�Գ�ʼ��map
	map<string, string> nameMap = {
		{"Feng","Junjie"},
		{"fuck","you"}
	};

	set<string> nameSet = { "Feng Junjie","fuck you" };
}

//mutimap��mutiset
void fcn3()
{
	vector<int> ivec;
	//ÿ�����ظ��洢����
	for (int i = 0; i < 100; i++)
	{
		ivec.push_back(i);
		ivec.push_back(i);
	}
	set<int> iset(ivec.cbegin(), ivec.cend());
	multiset<int> miset(ivec.cbegin(), ivec.cend());

	cout << "ivec size = " << ivec.size() << endl;
	cout << "iset size = " << iset.size() << endl;
	cout << "miset size = " << miset.size() << endl;
}

int main()
{
	fcn3();
	return 0;
}
