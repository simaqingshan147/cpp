//try语句块和异常处理
#include<iostream>
#include<string>
#include<stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::runtime_error;

enum Sex{man,woman };

typedef struct Student {
	string name;
	int age;
	Sex sex;
}Stu,*StrStu;

int main(void)
{
	Stu s;
	int i;
	cout << "Please enter a name" << endl;
	while (cin >> s.name)
	{
		try
		{
			if (s.name.size() <= 0 || s.name.size() > 5)
				throw runtime_error("Wrong name");
			else
				break;
		}
		catch (runtime_error err)
		{
			cout << err.what()
				<< "\nTry again? Enter y or n" << endl;
			char c;
			cin >> c;
			if (!cin || c == 'n')
				break;
		}
	}

	cout << "Pleasw enter an age" << endl;
	cin >> s.age;
	cout << "Please enter a sex\n"
		<< "1 for male and 0 for female" << endl;
	cin >> i;
	if (i == 1)
		s.sex = man;
	else if (!i)
		s.sex = woman;
	else
		s.sex = man;

	return 0;
}