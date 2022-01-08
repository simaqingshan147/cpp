//顺序容器操作
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<forward_list>
using namespace std;

//string追加字符
void knowledge1()
{
	string word;
	char c;
	while (cin >> c)
		word.push_back(c);

	cout << word << endl;
}


void knowledge2()
{
	//头插法
	list<int> ilist;
	for (size_t ix = 0; ix != 4; ++ix)
		ilist.push_front(ix);
}

void knowledge3()
{
	list<string> slist, v;
	v = { "quasi","simba","frollo","scar" };

	auto iter =--v.end();   //不能v.end()-2
	iter--;

	//把v后两位插入到slist开头
	slist.insert(slist.begin(), iter, v.end());

	//插入成功,insert返回第一个新加入元素的迭代器
	//插入失败,返回第一个参数
	string word;
	iter = slist.begin();
	//在头部反复插入
	//insert返回指向插入的第一个元素的迭代器
	while (cin >> word)
		iter = slist.insert(iter, word);
}

//emplace
void knowledge4()
{
	class a {
	public:
		int c;
		int d;
		//构造函数
		a() = default;
		a(int v1, int v2) { c = v1; d = v2; }
	};

	vector<a> item;
	//emplace成员使用参数直接构造元素
	
	//item.emplace(1, 2);  错误
	//item.push_back(1, 2);  错误
	item.push_back(a(1, 2));   //创建临时对象添加
	item.emplace_back();       //使用a的默认构造函数
	auto iter = item.begin();
	item.emplace(iter, 1, 2);   //使用a的构造函数,在开头添加临时对象
	item.emplace_back(1, 2);     //指定位置，自动构造
}

//访问元素
void knowledge5()
{
	vector<int> vi(10, -2);    //10个-2
	auto a = *vi.begin();
	auto a2 = vi.front();   //第一个数的引用
	auto b = *(--vi.end());
	auto b2 = vi.back();   //最后一个元素的引用,forward_list不支持

	//使用front和back要确保容器非空


	//改变front和back
	int& c = vi.back();
	c = 12;
	int& d = vi.back();
	d = 14;

	//快速随机访问
}

//删除元素
void knowledge6()
{
	//pop_back,pop_front
	vector<int> ilist(10, 1);
	while (!ilist.empty())
	{
		cout << ilist.back() << endl;
		ilist.pop_back();
		//vector没有pop_front元素
	}
	//froward_list不支持pop_back
	ilist = { 1,2,3,4,5,6,7,8 };
	auto it = ilist.begin();
	while (it != ilist.end())
	{
		if (*it % 2)
			it = ilist.erase(it);   //删除此元素,跳转至下一元素
		//erase返回删除元素的后一元素的迭代器
		else
			++it;
	}
	//要删除的第一个元素,要删除的最后一个元素之后的位置
	//删除后，it = ilist.end()
	it = ilist.erase(ilist.begin(), ilist.end());
	ilist.clear();  //删除所有元素
}

//特殊的forward_list操作
void knowledge7()
{
	//插入，删除影响前驱
	//给定参数是待处理节点前驱
	forward_list<int> flst = { 0,1,2,3,4,5,6,7,8,9 };
	auto prev = flst.before_begin();  //指向首元素之前的不存在元素，即头节点
	auto curr = flst.begin();         //首元素
	while (curr != flst.end())
	{
		if (*curr % 2)
			curr = flst.erase_after(prev);   //删除并移动curr
		else
		{
			prev = curr;
			++curr;  //同时向前移动
		}
	}
}

//改变容器大小
void knowledge8()
{
	list<int> ilist(10, 42);  //10个42
	ilist.resize(15);        //把5个0添加到ilist的末尾
	ilist.resize(25, -1);    //把10个-1添加到ilist末尾
	ilist.resize(5);         //删除后20个元素
}

//编写改变容器的循环程序
void knowledge9()
{
	//删除偶数元素，复制奇数元素
	vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
	auto iter = vi.begin();

	//end一直在更新，应该随时调用，而不是保存起来比较
	while (iter != vi.end())
	{
		if (*iter % 2)
		{
			iter = vi.insert(iter, *iter);
			iter += 2;  //iter指向插入元素,+2跳过插入元素和复制元素
		}
		else
		{
			iter = vi.erase(iter);
			//iter指向删除元素之后的元素
		}
	}
}

int main()
{
	
	return 0;
}