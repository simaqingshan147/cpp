//11.3.6  ---- 一个单词转换的map
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<iterator>
using namespace std;

//构建转换map
map<string, string>build_map(ifstream& map_file)
{
	map<string, string> trans_map;  //保存转换规则
	string key, value;
	
	//第一个单词为key，剩下的为value
	while (map_file >> key && getline(map_file, value))
	{
		//插入key,并跳过前导空格
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

//转换字符串
const string& transform(const string& s, const map<string, string>& m)
{
	auto it = m.find(s);
	if (it != m.cend())
		return it->second;   //替换
	
	return s;     //否则返回原字符串
}

//打印转换后字符串
void word_transform(ifstream& map_file, ifstream& input)
{
	auto trans_map = build_map(map_file);   //转换规则
	string text;
	while (getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;   //第一个单词不打印空格
		while (stream >> word)
		{
			if (firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

//测试build_map
void map_test(ifstream& map_file)
{
	auto mymap = build_map(map_file);
	cout << "map构建完成!" << endl;
	for (auto mpair : mymap)
		cout << mpair.first << " " << mpair.second << endl;
}

int main()
{
	ofstream map_file("map.txt", ofstream::app);
	ofstream inputFile("input.txt", ofstream::app);
	string word;
	
	//创建翻译规则文件
	if (map_file.is_open())
	{
		cout << "输入转换规则(输入-1退出)" << endl;
		cout << "输入要转换的单词:";
		cin >> word;
		while (word != "-1")
		{
			map_file << word << " ";
			cout << "输入" << word << "的目标单词:";
			cin >> word;
			map_file << word << "\n";

			cout << "输入要转换的单词:";
			cin >> word;
		}
		cout << "\n翻译规则文件完成!" << endl;
		map_file.close();
	}

	//创建翻译文件
	if (inputFile.is_open())
	{
		ostream_iterator<string> iter(inputFile, "\n");
		cout << "请输入待翻译的单词:(输入-1退出)";
		while (cin >> word && word != "-1")
		{
			*iter++ = word;
			cout << "请输入待翻译的单词:(输入-1退出)";
		}
		cout << "\n翻译文件创建完成!" << endl;
		inputFile.close();
	}

	//开始翻译
	ifstream mapFile("map.txt", fstream::in);
	ifstream input("input.txt", fstream::in);
	cout << "\n开始翻译:" << endl;
	if (mapFile.is_open() && input.is_open())
		word_transform(mapFile, input);
	else
		cout << "文件打开错误!";
	cout << "done!" << endl;
	mapFile.close();
	input.close();


	return 0;
}