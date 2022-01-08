//vectorģ����
#include<iostream>
#define DEFAULT_CAPACITY 100
typedef int Rank;  //��

//쳲���������
int fiboarray[] = { 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597 };

//vector��ģ��
template <typename T>class Vector{
protected:
	Rank _size; int _capacity; T* _elem;              //��ģ,����,������
	void copyFrom(T const* A, Rank lo, Rank hi);      //������������A[lo,hi]
	void expand();                                    //�ռ䲻��ʱ����
	void shrink();                                    //װ�����ӹ�Сʱѹ��

public:
	//���캯��
	Vector() = default;
	//����Ϊc,��ģΪs������Ԫ�س�ʼ��Ϊv
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
	{
		_elem = new T[_capacity = c];
		//s<=c
		for (_size = 0; _size < s; _elem[_size++] = v);  //ѭ��
	}
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }  //�������临��

	//��������
	~Vector() { delete[]_elem; }     //�ͷ��ڲ��ռ�

	//ֻ�����ʽӿ�  
	Rank size()const { return _size; }                    //��ģ
	bool empty()const { return !_size; }                  //�п�
	int disordered()const;                                //�ж������Ƿ�����
	Rank find(T const& e, Rank lo, Rank hi)const;         //���������������
	Rank find(T const& e)const{ return find(0, _size); }  //���������������
	Rank search(T const&e)const                           //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const;      //���������������

	//��д���ʽӿ�
	T& operator[](Rank r)const;                                                 //�����±������������������������ʽ���ø�Ԫ��
	Vector<T>& operator=(Vector<T>const&);                                      //���ظ�ֵ�����,�Ա��¡����
	T remove(Rank r);                                                           //ɾ����Ϊr������
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);                                            //����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); }                        //Ĭ�ϲ���β��
	void unsort(Rank lo, Rank hi);                                              //��������
	void unsort() { unsort(0, _size); }  //��������
	int deduplicate();                   //����ȥ��
	int uniquify();                      //����ȥ��

	//����
	void traverse(void(*)(T&));        //������ʹ�ú���ָ��,ֻ����ֲ����޸�
	template<typename VST>void traverse(VST&);    //����,ʹ�ú������󣬿�ȫ�����޸�
};

//���ڸ�ֵ��������
//������������A[lo,hi]
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;            //����ռ䣬��ģ����
	
	while (lo < hi)       //������_elem[0,hi-lo]
		_elem[_size++] = A[lo++];
	//ע������Ա��������ʹ��
}

//���ز��������ĸ�ֵ�����
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v)
{
	if (_elem)
		delete[]_elem;                //�ͷ�ԭ������
	copyFrom(v._elem, 0, V.size());   //���帴��
	return *this;                     //���ص�ǰ���������,�Ա���ʽ��ֵ       
}

//�����±������
//ʹ������������һ��ͨ���±�����
template<typename T> T& Vector<T>::operator[](Rank r)const
{
	return _elem[r];
}

//�����ռ䲻��ʱ����,�ӱ�����
template<typename T> void Vector<T>::expand()
{
	if (_size < _capacity)return;   //δ��,������
	//����������Ĭ������
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

	T* oldelem = _elem;
	_elem = new T[_capacity <<= 1];   //�����ӱ�
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;                 //�ͷ�ԭ�ռ�
}

//װ�����ӹ�Сʱѹ��������ռ�ռ�
template<typename T>void Vector<T>::shrink()
{
	//���������������Ĭ������
	if (_capacity < DEFAULT_CAPACITY << 1)return;
	//����ʱ����ģ��С���������ķ�֮һ
	if (_size << 2 > _capacity)return;

	T* oldelem = _elem;
	_elem = new T[_capacity >>= 1];   //������Сһ��
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete oldelem;                   //�ͷ�ԭ�ռ�
}

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

//�����㷨
//�����������,ʹԪ�صȸ��ʳ�����ÿһλ��
template<typename T>void permute(Vector<T>& v)
{
	for (int i = v.size(); i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

//��������
template<typename T>void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;  //����������Ϊ��һ����
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

//�������
template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	//�ж������Ԫ��,�����������
	//��·��ֵ,ǰһ��������ʱ������ֹ
	while ((lo < hi--) && (e != _elem[hi]));
	//����ʧ��,����-1
	return hi;
}

//����
template<typename T>
int Vector<T>::insert(Rank r, T const& e)
{
	expand();   //���б�Ҫ,����
	for (int i = r + 1; i <= _size; i++)
		_elem[i] = _elem[i - 1];
	_size++;
	_elem[r] = e;
	return r;
}

//����ɾ��
template<typename T>int Vector<T>::remove(Rank lo, Rank hi)
{
	//���������˻����
	if (lo == hi)return 0;
	while (hi<_size)_elem[lo++] = _elem[hi++];  //��hi��Ԫ������ǰ��
	_size = lo;  //lo�ƶ�������ĩ��
	shrink();    //���б�Ҫ,����
	return hi - lo;    //����ɾ����Ŀ
}

//��Ԫ��ɾ��
template<typename T> T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;     //���ر�ɾ��Ԫ��
}

//ɾ�������������ظ�Ԫ��
template<typename T>int Vector<T>::deduplicate()
{
	int oldsize = _size;
	Rank i = 1;
	//��ǰ׺��Ѱ����ͬ��(���һ��)
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove[i];
	return oldsize - _size;   //����ɾ������
}

//���ú���ָ����Ƶı���
template<typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

//���ú���������Ƶı���
template <typename T> template<typename	VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i])
			n++;
	}
	return n;       //nΪ��ʱ����
}

//���������ظ�Ԫ���޳�
template<typename T> int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;
	while (++j < _size)
	{
		//���в�ͬԪ�أ���ǰ��
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;   //i���������һ�����ظ�Ԫ�ص��±�
	shrink();    //ֱ�ӽض϶���Ԫ��
	return j - i;    //����ɾ��Ԫ�ظ���

}

//���ֲ���
//����֧
template<typename T>
static Rank binSearch1(T* A, T const& e, Rank lo, Rank hi)
{
	Rank mi;
	while (lo < hi)
	{
		mi = (lo + hi) >> 1;
		if (e < A[mi])hi = mi;
		else if (e > A[mi])lo = mi + 1;
		else return mi;
	}
	return -1;
}

//���ֲ��ң��汾2
//����֧
//������3��֧�汾������Ƚ�����,ʹ��������б��Ӱ��
template<typename T>
static Rank binSearch2(T* A, T const& e, Rank lo, Rank hi)
{
	Rank mi;
	//lo,hi����Ԫ��ʱ��ֹ
	while (1 < hi - lo)
	{
		mi = (lo + hi) >> 1;
		if (e < A[mi])hi = mi;//ȷ��[lo,mi]��[mi,hi]
		else lo = mi;         //����eҲ��һ������
	}
	//����Ԫ��λ��
	return (e == A[lo]) ? lo : -1;
	//����������,���ܷ����������
	//���ʧ��,���ܷ���ʧ��λ��

}

//���ֲ���,�汾3
template<typename T>
static Rank biSearch3(T* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)  //lo=mi+1,����ѭ����ֹʱlo=hi
	{
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi])
			hi = mi;
		//ȷ��[lo,mi]��[mi+1,hi]
		else     
			lo = mi + 1;   //��ʹ����,Ҳ����
	//A[0,lo-1]��Ԫ�ر�С�ڵ���e,A[lo,size-1]��Ԫ�رش���e
	// ���Խ���ʱ,A[lo-1]��С�ڵ���e,A[lo]�ش���e
	// �ɹ�,lo-1���������,ʧ��,lo-1Ҳ����ӽ�e����,��ʧ��λ��
	}
	return --lo;
	//�ж������,�ܷ����������
	//����ʧ��,����ʧ��λ��
}


//���������������
template<typename T>
Rank Vector<T>::search (T const& e, Rank lo, Rank hi) const
{
	return binSearch3(_elem, e, lo, hi);
}

int main()
{
	return 0;
}