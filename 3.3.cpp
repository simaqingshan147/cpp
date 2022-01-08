//vector,iterator
#include <vector>
#include<iostream>
#include<string>
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

vector<int> ivec; //ivec保存int类型的对象
vector<vector<string>> file; //该向量的元素是vector对象

int main()
{
	int i;
	ivec = { 1,2,3,4,5 };
	vector<int> ivec2(ivec); //copy ivec
	vector<int> ivec3 = ivec;
	vector<int> ivec4(10, -1); //elements number,element
	vector<int> ivec5(10);   //value initialized 0
	string s("some string!");

	/*
	//add elements
	for ( i = 6; i < 100; i++)
		ivec.push_back(i);
	for (auto i = 0; i < ivec.size(); i++)
		cout << ivec[i] << endl;
	*/

	/*
	//iterator
	auto a = ivec.begin();
	auto b = ivec.end();
	cout << *a << *++a << *--b << endl;
	*/

	if (s.begin() != s.end())
	{
		for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
			*it = toupper(*it);
		cout << s << endl;
	}
	/*
	vector<int>::iterator t1 = ivec.begin();
	vector<int>::const_iterator t2 = ++ivec.begin();  //only read
	//t1 = ivec.cbegin();  It's wrong
	t2 = ivec.cbegin();  //return only-read type
	*/

	/*
	for (auto it = s.cbegin();
		it != s.cend() && it->empty(); ++it)
		cout << *it << endl;
	*/

	return 0;
}