//�ļ��������
#include<fstream>
#include<iostream>
using namespace std;

int main()
{
	/*
	//д���ļ�
	//д�룬Ĭ�Ͻضϣ������ԭ���ݺ�����
	ofstream out("test.txt");  //��ʽoutģʽ����ʽ�ض�
	ofstream out1("test.txt", ofstream::out);   //��ʽ�ض�
	ofstream out2("test.txt", ofstream::out | ofstream::trunc);   //��ʽ�ض�

	//�����ļ����ݣ�������ʽָ��appģʽ
	//app �ļ�ĩβд��
	ofstream out3("test.txt", ofstream::out | ofstream::app);
	*/

	string temp;
	char buf[100];
	char c;
	
	ifstream infile("test.txt",istream::in);  //ֻ��ģʽ
	if (infile.is_open())   //����openʧ��,��failbit��λ
	{
		//ֱ�Ӷ�ȡ
		//���ո�ֹͣ���޷���ȡ�ո�
		while (infile >> temp)
			cout << temp << endl;

		infile.clear();                 //����״̬
		infile.seekg(istream::beg);    //�ص��ļ���ͷ
		//���ж�ȡ
		while (infile.getline(buf, sizeof(buf)))
			cout << buf << endl;

		infile.clear();
		infile.seekg(istream::beg);
		//���ַ���ȡ
		while ((c = infile.get()) != EOF)
			cout << c;
		cout << endl;
	}
	else
	{
		cout << "��ʧ��!" << endl;
		getchar();
	}
	infile.close();

	return 0;
}