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
	//�ƶ����캯��
	Vec(Vec<T>&&s)noexcept;
	//�ƶ���ֵ�����
	Vec<T>& operator=(Vec<T>&rhs)noexcept;
	void push_back(const T&);
	void push_back(T&&);  //�ƶ��汾��push_back
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
void Vec<T>::push_back(T&& s){
	chk_n_alloc();
	//sҲ����ֵ,��ʹ������ĳ��ֵ����ֵ����
	//�������move,construct��Ȼ�´��s
	alloc.construct(first_free++,std::move(s));
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
	/*
	//����move����ԭvector��Ԫ�����追��
	for (size_t i = 0; i != size(); i++)
		alloc.construct(dest++, std::move(*elem++));
	*/

	//�����ƶ�������,Ҳ���追��ԭvector
	//�ƶ���������֧��ԭ���������в������ع������������,������ֵ����
	//���ƶ����������ݸ��㷨
	dest = uninitialized_copy(make_move_iterator(begin()),
							make_move_iterator(end()),
							newData);

	free();  //�ͷ�ԭ�ڴ�
	element = newData;
	first_free = dest;
	cap = element + newCap;
}

//�ƶ�������������Դ��һ�㲻�׳��쳣
//noexcept�����������Ͷ����ж�ָ��
template<typename T>
Vec<T>::Vec(Vec<T>&&s) noexcept  //�ƶ��������׳��쳣
//��Ա��ʼ�����ӹ�s����Դ
:element(s.element),first_free(s.first_free),
	cap(s.cap){
		//�ƺ�Դ������ָ���ƶ�����Դ
		s.element = s.first_free = s.cap = nullptr;
	}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>& rhs) noexcept{
	//ֱ�Ӽ���Ը�ֵ
	if(this != &rhs)
	{
		free();
		//�ӹ���Դ
		element = rhs.element;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//rhs���ڿ�����״̬
		rhs.element = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

//Vec<int> getVec(istream& is){}

int main()
{
	Vec<int> v1,v2;
	int i = 5;
	v1.push_back(1);  //�ƶ�push_back
	v1.push_back(i);  //����push_back
	//�ƶ����캯���Ϳ������캯��ͨ������ƥ��ȷ��
	v2 = v1;  //v1����ֵ������

	//getVec������ֵ���ƶ�
	//��û���ƶ����캯��ʱ��Ҳ�ܵ��ÿ���
	//v2 = getVec(cin);

	cout<<"bye!"<<endl;
	return 0;
}