//13.3  ---- 交换操作
#include<iostream>
#include<string>
using namespace std;

//如果类定义了自己的swap操作,算法将使用类自定义版本
//直接调用标准库swap函数可能复制错误，或者降低性能

class Ptr {
public:
	//让swap函数访问数据成员
	friend void swap(Ptr&, Ptr&);
	Ptr& operator=(const Ptr);

	//默认构造函数
	Ptr() {
		i = 0;
		ps = new string();
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
		ps = other.ps;
		i = other.i;  
		use = other.use;
		++* use;  //递增计数
	}

	//析构函数
	~Ptr() {
		if (-- * use == 0)
		{
			delete ps;
			delete use;
		}
	}

	void show() const {
		cout << "use= " << *use << endl;
		cout << "ps= " << *ps << endl;
	}

private:
	string* ps;  //类指针复制，只复制指针
	int i;
	size_t* use;  //引用计数
};

//swap存在是为了优化性能,将其声明为inline函数
inline
void swap(Ptr& lptr, Ptr& rptr) {
	//使用标准库swap
	using std::swap;
	swap(lptr.ps, rptr.ps);  //交换指针，不是string数据
	swap(lptr.use, rptr.use);
	swap(lptr.i, rptr.i);
}

//用swap定义赋值运算符
//拷贝并交换,将左侧对象将右侧对象的副本进行交换
//自动处理自己赋值自己的情况，天然安全
//注意形参不是引用，只是副本
Ptr& Ptr::operator=(Ptr other) {
	swap(*this, other);
	return *this;
}

int main()
{
	Ptr test("hello");
	Ptr test2;
	test2 = test;
	test2.show();

	return 0;
}