//13.5 ---- 动态内存管理类
//例子 ---- 自建简化vector
#include<iostream>
#include<new>
#include<memory>
#include<utility>  //move
using namespace std;
/*
* 某些类需要在运行时分配动态内存
* 一般用vector等标准库容器
* 但有时需要自己进行内存分配
* 则必须定义自己的拷贝控制成员来管理分配内存
*/

//vector的简化实现
template<typename T>
class Vec {
public:
	Vec() : //默认构造函数,默认初始化了allocator
		element(nullptr), first_free(nullptr), cap(nullptr) {}
	//拷贝构造函数
	Vec(const Vec<T>&);
	//拷贝赋值运算符
	Vec<T>& operator=(const Vec<T>&);
	~Vec() { this->free(); };
	//移动构造函数
	Vec(Vec<T>&&s)noexcept;
	//移动赋值运算符
	Vec<T>& operator=(Vec<T>&rhs)noexcept;
	void push_back(const T&);
	void push_back(T&&);  //移动版本的push_back
	size_t size()const { return first_free - element; }
	size_t capacity()const { return cap - element; }
	T* begin()const { return element; }
	T* end()const { return first_free; }
private:
	//分配元素
	allocator<T> alloc;
	//首元素指针
	T* element;
	//第一个空闲元素指针,即vector的end
	T* first_free;
	//尾后位置指针,底层数组的end
	T* cap;
	//获得新内存
	void chk_n_alloc() {
		if (size() == capacity())reallocate();
	}
	//分配足够内存，并拷贝元素至新内存
	pair<T*, T*> alloc_n_copy
	(const T*, const T*);
	//释放内存
	void free();
	//获得更多元素并拷贝已有元素
	void reallocate();
};

template<typename T>
void Vec<T>::push_back(const T& s) {
	chk_n_alloc();  //确保有新内存
	//在first_free指向的元素中构造s的副本
	alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::push_back(T&& s){
	chk_n_alloc();
	//s也是左值,即使本身是某个值的右值引用
	//如果不用move,construct仍然会拷贝s
	alloc.construct(first_free++,std::move(s));
}

template<typename T>
pair<T*,T*>
Vec<T>::alloc_n_copy(const T* b, const T* e) {
	//b,e给定拷贝元素范围
	auto data = alloc.allocate(e - b);
	//first指向新内存的begin,second指向最后一个构造元素之后
	return { data,uninitialized_copy(b,e,data) };
}

template<typename T>
void Vec<T>::free() {
	if (element)//vec不为空
	{
		//逆序销毁元素
		for (auto p = first_free; p != element;)
			alloc.destroy(--p);
		//回收内存空间
		alloc.deallocate(element, cap - element);
	}
}

template<typename T>
Vec<T>::Vec(const Vec<T>& s) {
	//分配内存空间
	auto newdata = alloc_n_copy(s.begin(), s.end());
	element = newdata.first;
	//没有多余空间，指向同一元素
	first_free = cap = newdata.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs) {
	//分配内存
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	element = data.first;
	first_free = cap = data.second;
	return *this;
}

template<typename T>
void Vec<T>::reallocate() {
	//原vector为空，分配一个内存
	auto newCap = size() ? size() * 2 : 1;
	//分配新内存
	auto newData = alloc.allocate(newCap);
	auto dest = newData;  //新vector指针
	auto elem = element;
	/*
	//调用move，则原vector的元素无需拷贝
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	*/

	//调用移动迭代器,也无需拷贝原vector
	//移动迭代器，支持原迭代器所有操作，重构解引用运算符,返回右值引用
	//将移动迭代器传递给算法
	dest = uninitialized_copy(make_move_iterator(begin()),
							make_move_iterator(end()),
							newData);

	free();  //释放原内存
	element = newData;
	first_free = dest;
	cap = element + newCap;
}

//移动操作不分配资源，一般不抛出异常
//noexcept必须在声明和定义中都指定
template<typename T>
Vec<T>::Vec(Vec<T>&&s) noexcept  //移动操作不抛出异常
//成员初始化器接管s的资源
:element(s.element),first_free(s.first_free),
	cap(s.cap){
		//移后源对象不再指向被移动的资源
		s.element = s.first_free = s.cap = nullptr;
	}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>& rhs) noexcept{
	//直接检查自赋值
	if(this != &rhs)
	{
		free();
		//接管资源
		element = rhs.element;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//rhs置于可析构状态
		rhs.element = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

//Vec<int> getVec(istream& is){}

int main()
{
	Vec<int> v1,v2;
	int i = 5;
	v1.push_back(1);  //移动push_back
	v1.push_back(i);  //拷贝push_back
	//移动构造函数和拷贝构造函数通过函数匹配确定
	v2 = v1;  //v1是左值，拷贝

	//getVec返回右值，移动
	//当没有移动构造函数时，也能调用拷贝
	//v2 = getVec(cin);

	cout<<"bye!"<<endl;
	return 0;
}