//9.4 vvector对象如何增长
#include<iostream>
#include<vector>
#include<string>
#include<deque>
//动态连续存储
using namespace std;

//对于vector和string,部分实现渗透到接口中
//与内存分配部分互动
void knowledge1()
{
	vector<int> ivec(10, 100);
	string str = "string";
	deque<int> ide(10, 100);

	//shrink_to_fit,将容量capacity减小到size
	//具体实现可忽略此请求,即不一定缩容
	//只适用于vector,string,deque
	ivec.shrink_to_fit();
	str.shrink_to_fit();
	ide.shrink_to_fit();

	//capacity，显示容量
	//只适用于vector,string
	ivec.capacity();
	str.capacity();

	//reserve,分配内存空间
	//分配容量小于当前容量，忽略
	//只适用于vector,string
	ivec.reserve(1);   //忽略
	ivec.reserve(100);  //执行
	str.reserve(100);

	ivec.clear();
	cout << " ivec: size" << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	//新增24个元素
	for (vector<int>::size_type ix = 0; ix != 24; ++ix)
		ivec.push_back(ix);

	//size=24,capacity>24
	cout << "ivec.size: " << ivec.size()
		<< " capacity: " << ivec.capacity() << endl;
	//运行结果:size=24,capacity=28
}

int main()
{

	return 0;
}