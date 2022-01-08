//string流
#include<iostream>
#include<vector>
#include<sstream>   //string流头文件
#include<fstream>

using namespace std;

//个人信息类
struct PersonInfo {
	string name;
	//一个或多个电话号
	vector<string> phones;
};

void show(vector<PersonInfo> people)
{
	for (auto info : people)  
	{
		cout << "name:" << info.name << endl;
		for (auto tel : info.phones)
			cout << "		tel:" << tel << endl;
	}
}

int main()
{
	string line, word;
	vector<PersonInfo> people;
	ifstream file;
	file.open("people.txt", fstream::in);

	//逐行输入
	while (getline(file, line))
	{
		PersonInfo info;
		istringstream record(line);       //将记录绑定的读入的行
		record >> info.name;              //读取名字

		//名字，电话号间有空格
		while (record >> word)
			info.phones.push_back(word);  //追加电话号

		people.push_back(info);
	}
	file.close();
	show(people);

	//干，ztm方便
	return 0;
}