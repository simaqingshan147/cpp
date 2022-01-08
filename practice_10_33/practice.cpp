//��ϰʹ����������
#include<iostream>
#include<fstream>
#include<iterator>

using namespace std;

//���������ļ�num.txt
int createFile()
{
	ofstream num("num.txt", ostream::out);
	int i = 0;
	if (num.is_open())
	{
		ostream_iterator<int> iter(num, " ");
		while (i++ < 1000)
			*iter++ = rand();
		cout << "num.txtд�����" << endl;
		num.close();
	}
	else
		return -1;
	return 1;
}

//д������
int oddWrite(ofstream& file,ifstream& num)
{
	if (file.is_open())
	{
		ostream_iterator<int> odd(file, " ");
		if (num.is_open())
		{
			istream_iterator<int> iter(num);
			istream_iterator<int> eof;
			while (iter != eof)
			{
				if (*iter % 2 == 1)
					*odd++ = *iter;
				iter++;
			}
		}
		else
			return -1;
	}
	else
		return -1;
	return 1;
}

//д��ż��
int evenWrite(ofstream& file, ifstream& num)
{
	if (file.is_open())
	{
		ostream_iterator<int> even(file, "\n");
		if (num.is_open())
		{
			istream_iterator<int> iter(num);
			istream_iterator<int> eof;
			while (iter != eof)
			{
				if (*iter % 2 == 0)
					*even++ = *iter;
				iter++;
			}
		}
		else
			return -1;
	}
	else
		return -1;
	return 1;
}

int main()
{
	if (createFile())
	{
		ifstream num;
		num.open("num.txt", fstream::in);
		ofstream oddFile, evenFile;
		oddFile.open("odd.txt", fstream::app);
		evenFile.open("even.txt", fstream::app);
		if (num.is_open())
		{
			if (oddFile.is_open())
			{
				if(oddWrite(oddFile, num))
					cout << "�����ļ�д�����" << endl;
				num.close();
			}
			num.open("num.txt", fstream::in);
			if (evenFile.is_open())
			{
				if(evenWrite(evenFile, num))
					cout << "ż���ļ�д�����" << endl;
			}
			num.close();
			oddFile.close();
			evenFile.close();
		}
		return 0;
	}
}