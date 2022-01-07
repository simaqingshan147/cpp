//10.3.2 lambda表达式
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

void fcn1(void);
void fcn2(void);
void fcn3(void);
void fcn4(void);

//lambda表达式，可调用对象,可以理解为一个未命名的内联函数
//[捕获列表] (参数列表) -> 返回类型 {函数体}
//capture list：lambda函数中定义的局部变量列表
//必须使用尾置返回

void lambda()
{
	//把f定义为一个可调用对象
	//忽略括号相当于指定空参数列表
	//忽略返回类型，根据代码推断出来
	auto f = [] {return 42; };

	auto e = [](int a, int b)->int {if (a > b)return a; return b; };

	//使用调用运算符()调用lambda
	cout << f() << endl;
	cout << e(1, 2) << endl;
}

bool isShorter(const string& a, const string& b)
{
	return a.size() < b.size();
}

int main()
{
	vector<string> words;
	string temp;
	int sz = 5;
	//find_if算法,返回第一个使谓词返回非0值的元素
	//find_if只接受一元谓词

	cout << "请输入字符串(任意位置输入q终止):" << endl;
	while (cin >> temp && temp.find("q") == string::npos)
	{
		words.push_back(temp);
		cout << "请输入字符串(任意位置输入q终止):" << endl;
	}

	//按长度排序words
	stable_sort(words.begin(), words.end(), isShorter);

	//第一个长度大于5的字符串
	//用lambda作为一元谓词
	auto wc = find_if(words.begin(), words.end(),
		[sz](const string& a)
		{return a.size() >= sz; });

	size_t count = words.end() - wc;
	cout << count << " " << (count == 1 ? "word" : "words")
		<< " of length " << sz << " or longer" << endl;

	//for_each算法
	//对范围内的每个元素，执行谓词

	//打印长度大于sz的所有字符串
	for_each(wc, words.end(),
		[](const string& s) {cout << s << " "; });
	cout << endl;
	
	return 0;
}

//lambda捕获与返回

//拷贝捕获
void fcn1()
{
	size_t v1 = 42;  //局部变量
	auto f = [v1]{ return v1; };
	v1 = 0;
	auto j = f();  //j为42，不是0
	//捕获列表的v1是拷贝初始化的
}

//引用捕获
//warning：使用引用捕获，必须保证函数执行时引用变量存在
void fcn2()
{
	size_t v1 = 42;  //局部变量
	auto f = [v1] { return v1; };
	v1 = 0;
	auto j = f();  //j=0
}

//隐式捕获
void fcn3()
{
	int a = 10; int b = 20;

	auto f1 = [=] {return a; };  //自动拷贝捕获a
	auto f2 = [&] {return b; };  //自动引用捕获b

	//混合使用隐式捕获和显式捕获
	//=和&必须是第一个元素
	//显式与隐式捕获必须不同
	auto f3 = [=, &b] {if (a > b)return a; return b; };
	auto f4 = [&, b] {if (a > b)return a; return b; };
	a = 20; b = 0;
	cout << f1() << endl;  //10
	cout << f2() << endl;  //0
	cout << f3() << endl;  //10
	cout << f4() << endl;  //20
}

//可变lambda
void fcn4(void)
{
	//改变被捕获变量的值，加关键字mutable
	size_t v1 = 42;
	auto f = [v1]()mutable {return ++v1; };
	v1 = 0;
	auto j = f();  //43
}

//为lambda指定返回类型
void fcn5()
{
	//如果lambda包含return语句之外的其它语句,编译器假定返回void
	vector<int> vi(1, 10);
	/*
	错误,类型不匹配，无法重载函数
	transform(vi.begin(),vi.end(),vi.begin(),
		[](int i) {if (i < 0) return -1 * i; else return i; });
	*/
	transform(vi.begin(), vi.end(),vi.begin(),
		[](int i)->int{if (i < 0) return -1 * i; else return i; });
}