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

	void push_back(const T&);
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
	//调用move，则原vector的元素无需拷贝
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	free();  //释放原内存
	element = newData;
	first_free = dest;
	cap = element + newCap;
}

int main()
{
	Vec<int> v;
	for (int i = 0; i < 1000; i++)
		v.push_back(rand());
	for (int i : v)
		cout << i << endl;
	return 0;
}