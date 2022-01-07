//12.1.1 -- shared_ptr��
//�����ڴ����  -- StrBlob
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

	//Ԫ�ط���
	T& front();
	T& back();

private:
	//һ��ָ��vector<T>�Ĺ���ָ��
	shared_ptr<vector<T>> data;
	void check(size_type i, const string& msg)const;
};

//TBlobptr�����TBlob��
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

//���캯��
template<typename T>
TBlob<T>::TBlob() :data(make_shared<vector<T>>()) {}
//��ʼ���б�
template<typename T>
TBlob<T>::TBlob(initializer_list<T> il) :
	data(make_shared<vector<T>>(il)) {}


//����±�
template<typename T>
void TBlob<T>::check(size_type i, const string& msg) const {
	if (i >= data->size())
		throw out_of_range(msg);
}

template<typename T>
T& TBlob<T>::front()
{
	//vectorΪ��
	check(0, "front on empty TBlob");
	return data->front();
}

template<typename T>
T& TBlob<T>::back()
{
	//vectorΪ��
	check(0, "front on empty TBlob");
	return data->back();
}

template<typename T>
void TBlob<T>::pop_back()
{
	//vectorΪ��
	check(0, "front on empty TBlob");
	data->pop_back();
}

//TBlobPtr����

template<typename T>
shared_ptr<vector<T>> TBlobPtr<T>::check(size_t i, string& msg)
{
	auto ret = wptr.lock();
	if (!ret)  //vector������
		throw runtime_error("unbound TBlobPtr");
	if (i >= ret->size())
		throw out_of_range(msg);
	return ret;  //���򷵻�ָ��vector��shared_ptr
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