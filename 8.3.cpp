//string��
#include<iostream>
#include<vector>
#include<sstream>   //string��ͷ�ļ�
#include<fstream>

using namespace std;

//������Ϣ��
struct PersonInfo {
	string name;
	//һ�������绰��
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

	//��������
	while (getline(file, line))
	{
		PersonInfo info;
		istringstream record(line);       //����¼�󶨵Ķ������
		record >> info.name;              //��ȡ����

		//���֣��绰�ż��пո�
		while (record >> word)
			info.phones.push_back(word);  //׷�ӵ绰��

		people.push_back(info);
	}
	file.close();
	show(people);

	//�ɣ�ztm����
	return 0;
}