//11.3 --- ������������
#include<iostream>
#include<vector>
#include<set>
#include<map>

using namespace std;
map<string, size_t>word_count;

//�����������
void fcn1()
{
	vector<int> ivec = { 2,4,6,8,9,10 };
	set<int> set2;
	set2.insert(ivec.begin(), ivec.end());  //6��Ԫ��
	set2.insert({ 2,4,6,8,9 });  //ֻ������һ��Ԫ��,�ظ�ֵ����
	set2.insert(2);

	//ֻ����map����pair����
	word_count.insert({ "word",1 });  //��ʽ����pair
	word_count.insert(make_pair("word2", 1));
	word_count.insert(pair<string, int>("word3", 1));  //��ʽ����pair
	word_count.insert(map<string, int>::value_type("word4", 1));//��ʽ����pair
}

//map���뺯������һ��pair
//pair.first��ָ�����Ԫ�صĵ�����(Ҳ��pair)
//pair.second��bool������ɹ�Ϊtrue
void fcn2()
{
	map<string, size_t>word_count;
	string word;
	while (cin >> word)
	{
		//����ÿ������,��Ӧ������Ĭ��Ϊ1
		auto ret = word_count.insert({ word,1 });
		//����ʧ�ܣ�Ԫ���Ѵ���
		if (!ret.second)
			++ret.first->second;
		//ret.firstָ�����Ԫ�صĵ�����
		//ret.first->second����Ԫ�صĴ�����,��1
	}


	//����muti_map���������ǳɹ�����ΪԪ�������ظ�
	//muti_map.insert()����ָ����Ԫ�صĵ�����
	//���ط���bool����Ϊ����true
}

//��������ɾ��Ԫ��
void fcn3()
{
	//erase��ָ������ɾ���ü���Ӧ������Ԫ��
	//����ɾ��Ԫ�ص���Ŀ
	if (word_count.erase("word"))
		cout << "ok: " << "word" << " removed" << endl;
	else
		cout << "oops: " << "words" << "not found!" << endl;

	//�������ظ��ؼ��ֵ�����,ɾ��Ԫ����Ŀ���ܴ���1
}

//map��unordered_map֧���±������
//muti_map��muti_unordered_map��֧�֣���Ϊһ���ؼ��ֿ��ܶ�Ӧ���ֵ
//set��֧��,��Ϊֵ������ǹؼ���
void fcn4()
{
	//map�±�������Ԫ�أ�ֻ�ܶԷ�const��map����
	//���û��anna������anna�����Ѷ�Ӧֵ��Ϊ1
	word_count["anna"] = 1;
	//map�±귵����ֵ���ɶ�д
	cout << word_count["anna"];
	++word_count["anna"];
}

//����Ԫ��
void fcn5()
{
	if (word_count.find("anna") != word_count.end())
		cout << "anna is in the map" << endl;

	multimap<int, int> test;
	//mutimap��ȼ����ڴ洢����Ϊ�Ǻ����ʵ��
	for (int i = 0; i < 100; i++)
	{
		//�������ȵ�pair
		test.insert(make_pair(i, i + 1));
		test.insert(make_pair(i, i - 1));
	}

	//mutimap����1
	int search_item = 90;
	int enteries = test.count(search_item);  //Ԫ������
	auto iter = test.find(search_item);     //��һ��90
	while (enteries)
	{
		cout << iter->second << endl;   //��ӡ��Ӧֵ
		++iter;                         //��һ��90
		--enteries;
	}

	//mutimap����2
	auto begin = test.lower_bound(search_item);  //��һ��90
	auto end = test.upper_bound(search_item);    //���һ��90�ĺ�һλ
	for (; begin != end; begin++)
		cout << begin->second << endl;           //��ӡ����ֵ

	//mutimap����3
	//equal_range
	auto pos = test.equal_range(search_item);  //����һ��pair
	for (; pos.first != pos.second; ++pos.first)  //first��second��ɷ�Χ
		cout << pos.first->second << endl;
}

int main()
{
	//value_typeֵ����,map����pair
	//key_typeֵ����
	//����set,value_type��key_type��ͬ
	set<string>::value_type v1;  //string
	set<string>::key_type v2;  //Ҳ��string
}