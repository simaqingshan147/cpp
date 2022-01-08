//vector模板类
#include<iostream>
#define DEFAULT_CAPACITY 100
typedef int Rank;  //秩

//斐波那契数列
int fiboarray[] = { 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597 };

//vector类模板
template <typename T>class Vector{
protected:
	Rank _size; int _capacity; T* _elem;              //规模,容量,数据区
	void copyFrom(T const* A, Rank lo, Rank hi);      //复制数组区间A[lo,hi]
	void expand();                                    //空间不足时扩容
	void shrink();                                    //装填因子过小时压缩

public:
	//构造函数
	Vector() = default;
	//容量为c,规模为s，所有元素初始化为v
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
	{
		_elem = new T[_capacity = c];
		//s<=c
		for (_size = 0; _size < s; _elem[_size++] = v);  //循环
	}
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }  //数组区间复制

	//析构函数
	~Vector() { delete[]_elem; }     //释放内部空间

	//只读访问接口  
	Rank size()const { return _size; }                    //规模
	bool empty()const { return !_size; }                  //判空
	int disordered()const;                                //判断向量是否排序
	Rank find(T const& e, Rank lo, Rank hi)const;         //无序向量区间查找
	Rank find(T const& e)const{ return find(0, _size); }  //无序向量整体查找
	Rank search(T const&e)const                           //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const;      //有序向量区间查找

	//可写访问接口
	T& operator[](Rank r)const;                                                 //重载下标运算符，可以类似于数组形式引用个元素
	Vector<T>& operator=(Vector<T>const&);                                      //重载赋值运算符,以便克隆向量
	T remove(Rank r);                                                           //删除秩为r的向量
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);                                            //插入元素
	Rank insert(T const& e) { return insert(_size, e); }                        //默认插入尾端
	void unsort(Rank lo, Rank hi);                                              //区间置乱
	void unsort() { unsort(0, _size); }  //整体置乱
	int deduplicate();                   //无序去重
	int uniquify();                      //有序去重

	//遍历
	void traverse(void(*)(T&));        //遍历，使用函数指针,只读或局部性修改
	template<typename VST>void traverse(VST&);    //遍历,使用函数对象，可全局性修改
};

//基于赋值构建向量
//复制数组区间A[lo,hi]
template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;            //分配空间，规模清零
	
	while (lo < hi)       //复制至_elem[0,hi-lo]
		_elem[_size++] = A[lo++];
	//注意这里对变量的最大化使用
}

//重载操作向量的赋值运算符
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v)
{
	if (_elem)
		delete[]_elem;                //释放原有内容
	copyFrom(v._elem, 0, V.size());   //整体复制
	return *this;                     //返回当前对象的引用,以便链式赋值       
}

//重载下标运算符
//使向量能像数组一样通过下标引用
template<typename T> T& Vector<T>::operator[](Rank r)const
{
	return _elem[r];
}

//向量空间不足时扩容,加倍容量
template<typename T> void Vector<T>::expand()
{
	if (_size < _capacity)return;   //未满,不扩容
	//容量不低于默认容量
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

	T* oldelem = _elem;
	_elem = new T[_capacity <<= 1];   //容量加倍
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete[] oldelem;                 //释放原空间
}

//装填因子过小时压缩向量所占空间
template<typename T>void Vector<T>::shrink()
{
	//容量需大于两倍的默认容量
	if (_capacity < DEFAULT_CAPACITY << 1)return;
	//缩容时，规模需小于容量的四分之一
	if (_size << 2 > _capacity)return;

	T* oldelem = _elem;
	_elem = new T[_capacity >>= 1];   //容量缩小一半
	for (int i = 0; i < _size; i++)
		_elem[i] = oldelem[i];
	delete oldelem;                   //释放原空间
}

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

//置乱算法
//随机置乱向量,使元素等概率出现在每一位置
template<typename T>void permute(Vector<T>& v)
{
	for (int i = v.size(); i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

//区间置乱
template<typename T>void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;  //将子向量视为另一向量
	for (Rank i = hi - lo; i > 0; i--)
		swap(V[i - 1], V[rand() % i]);
}

//区间查找
template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	//有多个命中元素,返回秩最大者
	//短路求值,前一条件非真时立即中止
	while ((lo < hi--) && (e != _elem[hi]));
	//查找失败,返回-1
	return hi;
}

//插入
template<typename T>
int Vector<T>::insert(Rank r, T const& e)
{
	expand();   //如有必要,扩容
	for (int i = r + 1; i <= _size; i++)
		_elem[i] = _elem[i - 1];
	_size++;
	_elem[r] = e;
	return r;
}

//区间删除
template<typename T>int Vector<T>::remove(Rank lo, Rank hi)
{
	//单独处理退化情况
	if (lo == hi)return 0;
	while (hi<_size)_elem[lo++] = _elem[hi++];  //将hi后元素整体前移
	_size = lo;  //lo移动到了最末端
	shrink();    //如有必要,缩容
	return hi - lo;    //返回删除数目
}

//单元素删除
template<typename T> T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;     //返回被删除元素
}

//删除无序向量中重复元素
template<typename T>int Vector<T>::deduplicate()
{
	int oldsize = _size;
	Rank i = 1;
	//在前缀中寻找相同者(最多一个)
	while (i < _size)
		(find(_elem[i], 0, i) < 0) ? i++ : remove[i];
	return oldsize - _size;   //返回删除个数
}

//利用函数指针机制的遍历
template<typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

//利用函数对象机制的遍历
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
	return n;       //n为零时有序
}

//有序向量重复元素剔除
template<typename T> int Vector<T>::uniquify()
{
	Rank i = 0, j = 0;
	while (++j < _size)
	{
		//若有不同元素，向前移
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;   //i现在是最后一个不重复元素的下标
	shrink();    //直接截断多余元素
	return j - i;    //返回删除元素个数

}

//二分查找
//三分支
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

//二分查找，版本2
//两分支
//消除了3分支版本向右需比较两次,使查找树倾斜的影响
template<typename T>
static Rank binSearch2(T* A, T const& e, Rank lo, Rank hi)
{
	Rank mi;
	//lo,hi间无元素时中止
	while (1 < hi - lo)
	{
		mi = (lo + hi) >> 1;
		if (e < A[mi])hi = mi;//确定[lo,mi]或[mi,hi]
		else lo = mi;         //命中e也不一定结束
	}
	//返回元素位置
	return (e == A[lo]) ? lo : -1;
	//如果多个命中,不能返回秩最大者
	//如果失败,不能返回失败位置

}

//二分查找,版本3
template<typename T>
static Rank biSearch3(T* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)  //lo=mi+1,所以循环中止时lo=hi
	{
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi])
			hi = mi;
		//确定[lo,mi]或[mi+1,hi]
		else     
			lo = mi + 1;   //即使命中,也朝右
	//A[0,lo-1]中元素必小于等于e,A[lo,size-1]中元素必大于e
	// 所以结束时,A[lo-1]必小于等于e,A[lo]必大于e
	// 成功,lo-1是秩最大者,失败,lo-1也是最接近e的数,即失败位置
	}
	return --lo;
	//有多个命中,总返回秩最大者
	//查找失败,返回失败位置
}


//有序向量区间查找
template<typename T>
Rank Vector<T>::search (T const& e, Rank lo, Rank hi) const
{
	return binSearch3(_elem, e, lo, hi);
}

int main()
{
	return 0;
}