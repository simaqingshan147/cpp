//处理string对象中的字符
#include<iostream>
#include<cctype>

using std::string;
using std::cout;
using std::cin;
using std::endl;

//返回s中的标点符号数
void PunchNum(string s)
{
	//punct_cnt的类型为string::size_type
	decltype(s.size()) punct_cnt = 0;
	for (auto c : s)
	{
		if (std::ispunct(c))
			++punct_cnt;
	}
	cout << punct_cnt
		<< " punctuation chracters in " << s << endl;
}

//把s转化为大写
void AllUpper(string s)
{
	//c是引用，因此赋值语句将改变s中字符的值s
	for (auto& c : s)
		c = std::toupper(c);
	cout << s << endl;
}

int main()
{
	
	//每行输出一个字符
	string str("some,string");
	/*
	//范围for语句
	for (auto c : str)  //c是char类型
		cout << c << endl;
	*/
	//PunchNum(str);
	AllUpper(str);
	return 0;
}