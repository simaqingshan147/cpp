//12.1.1 -- shared_ptr类
//共享内存的类  -- StrBlob
#include<iostream>
#include<vector>
#include<string>
#include<memory>
using namespace std;

template<typename T>
class TBlob {
public:
	typedef T size_type;

	TBlob();
	TBlob(initializer_list<T> il);
	
	size_type size()const { return data->size(); }
	bool empty()const { return data->empty(); }
	void push_pack(const T& t) { data->push_back(t); }
	void pop_back();

	//元素访问
	T& front();
	T& back();

private:
	//一个指向vector<T>的共享指针
	shared_ptr<vector<T>> data;
	void check(size_type i, const string& msg)const;
};

//TBlobptr：检测TBlob类
template<typename T>
class TBlobPtr {
public:
	TBlobPtr():current_exception(0){}
	TBlobPtr(TBlob &t,size_t sz = 0):
		wptr(t.data),curr(sz){}

private:
	shared_ptr<vector<T>> check(size_t, string&)const;
	weak_ptr<vector<T>> wptr;
	size_t curr;
};

//构造函数
template<typename T>
TBlob<T>::TBlob() :data(make_shared<vector<T>>()) {}
//初始化列表
template<typename T>
TBlob<T>::TBlob(initializer_list<T> il) :
	data(make_shared<vector<T>>(il)) {}


//检查下标
template<typename T>
void TBlob<T>::check(size_type i, const string& msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

template<typename T>
T& TBlob<T>::front()
{
	//vector为空
	check(0, "front on empty TBlob");
	return data->front();
}

template<typename T>
T& TBlob<T>::back()
{
	//vector为空
	check(0, "front on empty TBlob");
	return data->back();
}

template<typename T>
void TBlob<T>::pop_back()
{
	//vector为空
	check(0, "front on empty TBlob");
	data->pop_back();
}

//TBlobPtr函数

template<typename T>
shared_ptr<vector<T>> TBlobPtr<T>::check(size_t i, string& msg)
{
	auto ret = wptr.lock();
	if (!ret)  //vector被销毁
		throw runtime_error("unbound TBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;  //否则返回指向vector的shared_ptr
}

int main()
{
	TBlob<int> test1;
	for (int i = 0; i < 100; i++)
		test1.push_pack(i);
	cout << "front:" << test1.front() << endl;
	cout << "back: " << test1.back() << endl;
	return 0;
}