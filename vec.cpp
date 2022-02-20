//13.5 ---- ��̬�ڴ������
//���� ---- �Խ���vector
#include<iostream>
#include<new>
#include<memory>
#include<utility>  //move
using namespace std;
/*
* ĳЩ����Ҫ������ʱ���䶯̬�ڴ�
* һ����vector�ȱ�׼������
* ����ʱ��Ҫ�Լ������ڴ����
* ����붨���Լ��Ŀ������Ƴ�Ա����������ڴ�
*/

//vector�ļ�ʵ��
template<typename T>
class Vec {
public:
	Vec() : //Ĭ�Ϲ��캯��,Ĭ�ϳ�ʼ����allocator
		element(nullptr), first_free(nullptr), cap(nullptr) {}
	//�������캯��
	Vec(const Vec<T>&);
	//������ֵ�����
	Vec<T>& operator=(const Vec<T>&);
	~Vec() { this->free(); };

	void push_back(const T&);
	size_t size()const { return first_free - element; }
	size_t capacity()const { return cap - element; }
	T* begin()const { return element; }
	T* end()const { return first_free; }
private:
	//����Ԫ��
	allocator<T> alloc;
	//��Ԫ��ָ��
	T* element;
	//��һ������Ԫ��ָ��,��vector��end
	T* first_free;
	//β��λ��ָ��,�ײ������end
	T* cap;
	//������ڴ�
	void chk_n_alloc() {
		if (size() == capacity())reallocate();
	}
	//�����㹻�ڴ棬������Ԫ�������ڴ�
	pair<T*, T*> alloc_n_copy
	(const T*, const T*);
	//�ͷ��ڴ�
	void free();
	//��ø���Ԫ�ز���������Ԫ��
	void reallocate();
};

template<typename T>
void Vec<T>::push_back(const T& s) {
	chk_n_alloc();  //ȷ�������ڴ�
	//��first_freeָ���Ԫ���й���s�ĸ���
	alloc.construct(first_free++, s);
}

template<typename T>
pair<T*,T*>
Vec<T>::alloc_n_copy(const T* b, const T* e) {
	//b,e��������Ԫ�ط�Χ
	auto data = alloc.allocate(e - b);
	//firstָ�����ڴ��begin,secondָ�����һ������Ԫ��֮��
	return { data,uninitialized_copy(b,e,data) };
}

template<typename T>
void Vec<T>::free() {
	if (element)//vec��Ϊ��
	{
		//��������Ԫ��
		for (auto p = first_free; p != element;)
			alloc.destroy(--p);
		//�����ڴ�ռ�
		alloc.deallocate(element, cap - element);
	}
}

template<typename T>
Vec<T>::Vec(const Vec<T>& s) {
	//�����ڴ�ռ�
	auto newdata = alloc_n_copy(s.begin(), s.end());
	element = newdata.first;
	//û�ж���ռ䣬ָ��ͬһԪ��
	first_free = cap = newdata.second;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs) {
	//�����ڴ�
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	element = data.first;
	first_free = cap = data.second;
	return *this;
}

template<typename T>
void Vec<T>::reallocate() {
	//ԭvectorΪ�գ�����һ���ڴ�
	auto newCap = size() ? size() * 2 : 1;
	//�������ڴ�
	auto newData = alloc.allocate(newCap);
	auto dest = newData;  //��vectorָ��
	auto elem = element;
	//����move����ԭvector��Ԫ�����追��
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	free();  //�ͷ�ԭ�ڴ�
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