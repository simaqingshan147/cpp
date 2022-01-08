//10.3.4 参数绑定
//bind函数 通用函数适配器
#include<iostream>
#include<algorithm>
#include<functional>  //bind函数,placeholders命名空间,ref函数
#include<vector>
#include<string>

using namespace std;

bool isShorter(const string& a, const string& b){ return a.size() < b.size(); }
bool check_size(const string& s, int size) { return s.size() > size; }

void fcn1()
{
	//有捕获变量的lambda不容易被函数代替
	//因为泛型算法对几元谓词有限制
	//即函数中不能有多的形参传递捕获变量

	/*
	bind函数
	auto newfun = bind(fun,arg_list);
	newfun和fun都是可调用对象
	arg_list参数列表
	调用newfun，相当于调用fun(arg_list)
	*/

	//_n:占位符,表示传入新函数的参数
	// _n表示是新函数的第n个参数
	// 占位符的个数是新函数的参数个数
	

	//check(_1) = check(_1,6)
	auto check6 = bind(check_size, placeholders::_1, 6);
	string s = "hello!";
	cout << check6(s) << endl;
}

int main()
{
	vector<string> words;
	string temp;
	int sz = 5;

	cout << "请输入字符串(任意位置输入q终止):" << endl;
	while (cin >> temp && temp.find("q") == string::npos)
	{
		words.push_back(temp);
		cout << "请输入字符串(任意位置输入q终止):" << endl;
	}

	//按长度排序words
	stable_sort(words.begin(), words.end(), isShorter);

	/*
	* lambda实现
	auto wc = find_if(words.begin(), words.end(),
		[sz](const string& a)
		{return a.size() >= sz; });
	*/

	//bind实现
	auto wc = find_if(words.begin(), words.end(),
		bind(check_size, placeholders::_1, sz));

	size_t count = words.end() - wc;
	cout << count << " " << (count == 1 ? "word" : "words")
		<< " of length " << sz << " or longer" << endl;

	for_each(wc, words.end(),
		[](const string& s) {cout << s << " "; });
	cout << endl;

	return 0;
}

//bind的参数映射
int myf(int a, int b, int c, int d, int e) { return a; }

void fcn2()
{
	int a = 10; int b = 10; int c = 10;
	//g(_1,_2) = myf(a,b,_2,c,_1)
	auto g = bind(myf, a, b, placeholders::_2, c, placeholders::_1);

	//bind中不是占位符的参数默认拷贝
	//不能拷贝的参数,使用标准库ref

	//输出流不能拷贝，只能引用
	auto myprint = bind(fprintf, ref(cout), placeholders::_1);
}