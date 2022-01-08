//类的其他特性
#include<iostream>
#include<vector>
#include<string>

using std::string;
using std::ostream;
using std::istream;
using std::vector;
using std::cout;
using std::cin;

//窗口管理类
//表示显示器上的一组screen
class Window_mgr {
public:
	using ScreenIndex = vector<Screen>::size_type;
	ScreenIndex addScreen(const Screen&);
private:
	//默认情况下,包含一个标准尺寸的空白screen,类内初始值
	vector<Screen> screens{ Screen(24,80, ' ') };         //列表初始化
	void clear(ScreenIndex);
};

//显示器窗口类
class Screen {
public:
	typedef string::size_type pos;
	//using pos = string::size_type;

	Screen() = default;
	Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){}
	Screen(pos ht,pos wd,char c):height(ht),width(wd),
		contents(ht*wd,c){}

	char get()const{                            //读取光标字符           
		some_number();
		return contents[cursor];                //隐式内联
	}
	inline char get(pos ht, pos wd)const;       //显式内联
	Screen& move(pos r, pos c);

	void some_number()const;

	Screen& set(char);
	Screen& set(pos, pos, char);

	//根据对象是否是const重载display函数
	//该函数调用do_display时this隐式转换为指向const的指针,返回非常量引用
	Screen& display(ostream& os) { do_display(os); return *this; }
	//该函数返回常量引用
	const Screen& display(ostream& os)const { do_display(os); return *this; }
private:
	pos cursor = 0;                            //光标位置
	pos height = 0, width = 0;                 //高，宽
	string contents;

	//可变数据成员
	mutable size_t access_ctr = 0;                //记录成员函数调用次数

	//该函数负责显示screen的内容
	//指向非常量的this指针被const隐式转换为指向常量的指针
	void do_display(ostream& os)const { os << contents; }

	//友元声明仅仅影响访问权限,不是真正的声明
	friend void Window_mgr::clear(ScreenIndex);
};

//可在函数定义处指定inline
//移动光标,隐含this形参
inline Screen& Screen::move(pos r, pos c)
{
	pos row = r * width;   //计算行位置
	cursor = row + c;      //将光标移动的指定列
	some_number();
	return *this;
}

//在类的内部声明成inline
//返回指定位置的字符
char Screen::get(pos r, pos c)const
{
	pos row = r * width;
	some_number();
	return contents[row + c];
}

//计算成员函数调用次数
void Screen::some_number()const
{
	//可变数据成员永远不是const，即使它是const成员的对象
	//因此,一个const成员函数可以改变一个可变成员的值
	++access_ctr;
}

//设置光标所在位置的字符
inline Screen& Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
	//返回的是对象本身，不是对象的副本
}

//设置指定位置的字符
inline Screen& Screen::set(pos r, pos col, char ch)
{
	//内联函数,可以读取类数据成员
	contents[r * width + col] = ch;
	return *this;
}

void Window_mgr::clear(ScreenIndex i)
{
	Screen& s = screens[i];
	//把类设为友元,则友元类的成员函数可以访问此类所有成员,包括private
	//现在是友元函数
	s.contents = string(s.height * s.width, ' ');
}

//返回类型使用的名字都位于类的作用域之外
//返回类型必须指明它是哪个类的成员
//向窗口添加一个Screen，返回它的编号
Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen& s)
{
	screens.push_back(s);
	return screens.size() - 1;
}

int main()
{
	Screen myscreen;
	const Screen blank(8, 10);
	myscreen = Screen(8, 10);
	Screen::pos ht = 24, wd = 80;
	Screen scr(ht, wd, ' ');

	Screen* p = &scr;
	char c = scr.get();     //访问scr对象的get成员
	c = p->get();			//访问p所指对象的get成员

	//两个操作都会在myscreen上依次进行
	//因为move和set返回引用,改变的是对象本身
	myscreen.move(4, 0).set('#');

	myscreen.display(cout);     //调用非常量版本
	blank.display(cout);        //调用常量版本

	return 0;
}