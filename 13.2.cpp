//13.2 ---- 拷贝控制和资源管理
#include<iostream>
#include<string>
using namespace std;

//类值拷贝,每个类的值有自己的副本
//类指针拷贝,每个类共享底层对象，改变副本也改变源对象

//行为像值的类
class a {
public:
	int num;
	//此环境下视为每个指针指向不同的string,则str为类值拷贝
	string* str;	

	a() {
		num = 0;
		str = new string();
	}

	~a() {
		delete str;
	}

	//拷贝构造函数,直接拷贝值
	a(const a& other) {
		num = other.num;

		//*str = *other.str;
		//错误，不相干的类成员指向同一内存
		//delete str就把另一个也delete了

		auto newp = new string(*other.str);
		delete str;
		str = newp;
	}

	//拷贝赋值运算符整合析构函数和构造函数的操作
	//销毁左侧对象资源，从右侧对象拷贝数据
	//一定要有正确的顺序,要做到将自己赋给自己也能正常工作
	a& operator=(const a& other) {
		//拷贝右侧数据
		//不拷贝，直接删除再赋值，想想赋给自己能正常吗
		auto newp = new string(*other.str);

		//释放旧内存
		delete str;
		//拷贝到左侧
		num = other.num;
		str = newp;
		
		//返回本对象
		return *this;
	}
};

//行为像指针的类
//直接管理资源，需自定义引用计数
//引用计数应保存在动态内存中，这样修改计数就是全局修改
class Ptr {
public:
	//默认构造函数
	Ptr() {
		i = 0;
		ps = new string();    //默认为空字符串
		//计数器初始化为1，因为空字符串也可以被引用
		use = new size_t(1);
	}

	//指定str的构造函数
	Ptr(const string& s) {
		//不能直接*ps = s,s会销毁
		ps = new string(s);
		i = 0;
		use = new size_t(1); //计数器初始化为1
	}
	
	//拷贝构造函数
	Ptr(const Ptr& other) {
		//拷贝指针，指向相同内存
		ps = other.ps;
		i = other.i;  //这个是值拷贝

		//连计数器一起拷贝，指向相同计数器
		//这个是拷贝初始化，没有原计数器
		use = other.use;
		++*use;  //递增计数
	}

	//拷贝赋值运算符
	//考虑自己复制自己的情况，先递增后递减，计数不变
	Ptr& operator=(const Ptr& other) {
		//递增右侧拷贝计数
		++* other.use;
		//递减原计数
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
		//拷贝
		ps = other.ps;
		i = other.i;
		use = other.use;
		return *this;  //返回本对象
	}

	//析构函数
	~Ptr() {

		//只能递减引用计数
		//引用计数为0时才能销毁
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
	}

	//显示
	void show() const {
		cout << "use= " << *use << endl;
		cout << "ps= " << *ps << endl;
	}

private:
	string* ps;  //类指针复制，只复制指针
	int i;
	size_t* use;  //引用计数
};

int main()
{
	
	a test;
	test.num = 1;
	*test.str = "hello";
	a test2(test);
	cout << test2.num<<" " << *test2.str << endl;
	

	Ptr p1("hello");
	//拷贝初始化
	Ptr p2(p1);
	cout << "p1: "; p1.show();
	cout << "p2: "; p2.show();
	//自我拷贝
	p1 = p1;
	cout << "p1: "; p1.show();

	return 0;
}