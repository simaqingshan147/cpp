//11.3 --- 关联容器操作
#include<iostream>
#include<vector>
#include<set>
#include<map>

using namespace std;
map<string, size_t>word_count;

//插入关联容器
void fcn1()
{
	vector<int> ivec = { 2,4,6,8,9,10 };
	set<int> set2;
	set2.insert(ivec.begin(), ivec.end());  //6个元素
	set2.insert({ 2,4,6,8,9 });  //只插入了一个元素,重复值无视
	set2.insert(2);

	//只能向map插入pair类型
	word_count.insert({ "word",1 });  //隐式构造pair
	word_count.insert(make_pair("word2", 1));
	word_count.insert(pair<string, int>("word3", 1));  //显式构造pair
	word_count.insert(map<string, int>::value_type("word4", 1));//显式构造pair
}

//map插入函数返回一个pair
//pair.first是指向插入元素的迭代器(也是pair)
//pair.second是bool，插入成功为true
void fcn2()
{
	map<string, size_t>word_count;
	string word;
	while (cin >> word)
	{
		//插入每个单词,对应存在数默认为1
		auto ret = word_count.insert({ word,1 });
		//插入失败，元素已存在
		if (!ret.second)
			++ret.first->second;
		//ret.first指向存在元素的迭代器
		//ret.first->second，该元素的存在数,加1
	}


	//对于muti_map，插入总是成功，因为元素允许重复
	//muti_map.insert()返回指向新元素的迭代器
	//不必返回bool，因为总是true
}

//关联容器删除元素
void fcn3()
{
	//erase，指定键，删除该键对应的所有元素
	//返回删除元素的数目
	if (word_count.erase("word"))
		cout << "ok: " << "word" << " removed" << endl;
	else
		cout << "oops: " << "words" << "not found!" << endl;

	//允许保存重复关键字的容器,删除元素数目可能大于1
}

//map和unordered_map支持下标运算符
//muti_map和muti_unordered_map不支持，因为一个关键字可能对应多个值
//set不支持,因为值本身就是关键字
void fcn4()
{
	//map下标会插入新元素，只能对非const的map操作
	//如果没有anna，插入anna，并把对应值赋为1
	word_count["anna"] = 1;
	//map下标返回左值，可读写
	cout << word_count["anna"];
	++word_count["anna"];
}

//查找元素
void fcn5()
{
	if (word_count.find("anna") != word_count.end())
		cout << "anna is in the map" << endl;

	multimap<int, int> test;
	//mutimap相等键相邻存储，因为是红黑树实现
	for (int i = 0; i < 100; i++)
	{
		//插入键相等的pair
		test.insert(make_pair(i, i + 1));
		test.insert(make_pair(i, i - 1));
	}

	//mutimap查找1
	int search_item = 90;
	int enteries = test.count(search_item);  //元素数量
	auto iter = test.find(search_item);     //第一个90
	while (enteries)
	{
		cout << iter->second << endl;   //打印对应值
		++iter;                         //下一个90
		--enteries;
	}

	//mutimap查找2
	auto begin = test.lower_bound(search_item);  //第一个90
	auto end = test.upper_bound(search_item);    //最后一个90的后一位
	for (; begin != end; begin++)
		cout << begin->second << endl;           //打印对于值

	//mutimap查找3
	//equal_range
	auto pos = test.equal_range(search_item);  //返回一个pair
	for (; pos.first != pos.second; ++pos.first)  //first和second组成范围
		cout << pos.first->second << endl;
}

int main()
{
	//value_type值类型,map的是pair
	//key_type值类型
	//对于set,value_type和key_type相同
	set<string>::value_type v1;  //string
	set<string>::key_type v2;  //也是string
}