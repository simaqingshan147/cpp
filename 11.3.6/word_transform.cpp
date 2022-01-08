//11.3.6  ---- һ������ת����map
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<iterator>
using namespace std;

//����ת��map
map<string, string>build_map(ifstream& map_file)
{
	map<string, string> trans_map;  //����ת������
	string key, value;
	
	//��һ������Ϊkey��ʣ�µ�Ϊvalue
	while (map_file >> key && getline(map_file, value))
	{
		//����key,������ǰ���ո�
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	}
	return trans_map;
}

//ת���ַ���
const string& transform(const string& s, const map<string, string>& m)
{
	auto it = m.find(s);
	if (it != m.cend())
		return it->second;   //�滻
	
	return s;     //���򷵻�ԭ�ַ���
}

//��ӡת�����ַ���
void word_transform(ifstream& map_file, ifstream& input)
{
	auto trans_map = build_map(map_file);   //ת������
	string text;
	while (getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;   //��һ�����ʲ���ӡ�ո�
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

//����build_map
void map_test(ifstream& map_file)
{
	auto mymap = build_map(map_file);
	cout << "map�������!" << endl;
	for (auto mpair : mymap)
		cout << mpair.first << " " << mpair.second << endl;
}

int main()
{
	ofstream map_file("map.txt", ofstream::app);
	ofstream inputFile("input.txt", ofstream::app);
	string word;
	
	//������������ļ�
	if (map_file.is_open())
	{
		cout << "����ת������(����-1�˳�)" << endl;
		cout << "����Ҫת���ĵ���:";
		cin >> word;
		while (word != "-1")
		{
			map_file << word << " ";
			cout << "����" << word << "��Ŀ�굥��:";
			cin >> word;
			map_file << word << "\n";

			cout << "����Ҫת���ĵ���:";
			cin >> word;
		}
		cout << "\n��������ļ����!" << endl;
		map_file.close();
	}

	//���������ļ�
	if (inputFile.is_open())
	{
		ostream_iterator<string> iter(inputFile, "\n");
		cout << "�����������ĵ���:(����-1�˳�)";
		while (cin >> word && word != "-1")
		{
			*iter++ = word;
			cout << "�����������ĵ���:(����-1�˳�)";
		}
		cout << "\n�����ļ��������!" << endl;
		inputFile.close();
	}

	//��ʼ����
	ifstream mapFile("map.txt", fstream::in);
	ifstream input("input.txt", fstream::in);
	cout << "\n��ʼ����:" << endl;
	if (mapFile.is_open() && input.is_open())
		word_transform(mapFile, input);
	else
		cout << "�ļ��򿪴���!";
	cout << "done!" << endl;
	mapFile.close();
	input.close();


	return 0;
}