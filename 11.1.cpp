//11.1 使用关联容器
#include<iostream>
#include<map> //map和允许关键字相同的map
#include<set> //set和允许关键字相同的set
#include<unordered_map>  //哈希组织的map
#include<unordered_set>  //哈希组织的set
#include<string>

using namespace std;

//统计每个单词在输入中出现的次数
void fcn1()
{
	//键string,值size_t
	map<string, size_t> word_count;
	string word;
	
	//要忽略的单词统计到set中
	set<string> exclude = { "The","But","And","Or","An","A",
							"the","but","and","or","an","a" };

	cout << "请输入:";
	while (cin >> word)
	{
		//只统计不在exclude中的值
		//find，找到了返回目标迭代器，否则返回尾迭代器
		if(exclude.find(word)==exclude.end())
			++word_count[word];  //单词对应的值加1
		cout << "请输入:";
	}

	//pair模板类型,first成员保存键,second成员保存值
	for (const auto& w : word_count)
		cout << w.first << " occurs " << w.second
		<< ((w.second > 1) ? " times" : " time") << endl;
}

//值初始化关联容器
void fcn2()
{
	//键-值对初始化map
	map<string, string> nameMap = {
		{"Feng","Junjie"},
		{"fuck","you"}
	};

	set<string> nameSet = { "Feng Junjie","fuck you" };
}

//mutimap和mutiset
void fcn3()
{
	vector<int> ivec;
	//每个数重复存储两次
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
