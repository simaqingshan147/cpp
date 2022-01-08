//11.4 ———— 无序（哈希）容器
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>
#include<unordered_set>
using namespace std;

//无序容器，散列实现
//冲突处理方法可能是链表法(?)

class myCla {
public:
	string str;
	int num;
};

//判断相等
bool isSame(myCla& a, myCla& b) { return a.num == b.num; }

//自建hash函数
//string类型的hash值
//hash是个模板(类)
size_t hasher(const myCla& a) { return hash<string>()(a.str); }


int main()
{
	//类型是内置类型时，直接定义
	//因为内置类型有自己的hash函数和比较相等的方法
	unordered_map<string,string> myMap;
	unordered_multiset<int> aset(32);  //每行链表节点的个数
	unordered_multiset<int> bset;      //不指定也行

	//首先为自己类的set定义一个类型别名
	//自建的无序容器必须指定hash函数和比较相等的函数
	using myCla_mutiset = 
		unordered_multiset<myCla, decltype(hasher)*, decltype(isSame)*>;

	//每行链表节点的个数,哈希函数指针,相等判断函数指针
	//自建的必须指定链表节点个数
	myCla_mutiset myset(42,hasher, isSame);  //隐式构造
	myCla a = { "string",1 };
	//myCla b("string", 1); 需要构造函数
	myCla b; b.str = "string"; b.num = 2;
	
	//使用
	myset.insert(a);
	myset.insert(b);

	return 0;
}