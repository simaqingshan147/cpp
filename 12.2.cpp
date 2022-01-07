//��̬����
#include<iostream>
#include<new>
#include<memory>  //allocator
#include<vector>
using namespace std;

void fcn1()
{
	int* p = new int[42]();  //��������,42��ֵ��ʼ��Ϊ0

	//����̬���������ָ��
	unique_ptr<int[]> up(p);

	//ָ������ʱ��ʹ���±�
	for (int i = 0; i < 42; i++)
		cout << up[i] << " ";
	cout << endl;
	up.release();  //�൱�ڵ���delete[]

	//shared_ptr��ֱ��֧�ֹ���̬����
	//���붨��ɾ����
	//��ΪĬ�����shared_ptr��delete����

	//�������ǲ�����deleteֱ�����ٵĶ�Ҫ����ɾ����

	//��lambda����ɾ����
	shared_ptr<int> sp(p, [](int* p) {delete[] p; });
}

//allocator��
//���ڴ�����빹��������
void fcn2()
{
	allocator<string> alloc;  
	auto const p = alloc.allocate(10);  //����10��δ�����string
	auto q = p;
	//cout << *q << endl; δ����:ʹ����δ���������ڴ�

	alloc.construct(q++);  //*qΪ���ַ���
	alloc.construct(q++, 10, 'c');  //*q = ccccccccccc
	alloc.construct(q++, "hi");

	//q֮ǰ���ǹ����Ԫ��
	while (q != p)
		alloc.destroy(--q);  //�ͷŹ����string

	//q����������ʹ��
	//���߹黹�ڴ��ϵͳ
	alloc.deallocate(p, 10);
	//ָ�����ָ������ڴ棬��С���������ʱ��ͬ
}

//���������δ��ʼ���ڴ���㷨
//�ڴ�δ��ʼ��������ֱ�ӿ���
void fcn3()
{
	vector<int> vi = { 1,2,3,4,5,6,7,8,9,10 };
	
	allocator<int> alloc;
	auto p = alloc.allocate(vi.size() * 2);  //������Ķ�̬�ڴ�

	//����vi��δ��ʼ���ڴ棬����ָ�����һ����֮����ڴ��ָ��
	auto q = uninitialized_copy(vi.begin(), vi.end(), p);
	//ʣ���ڴ��ʼ��Ϊ42
	//ָ�룬��ֵԪ����������ֵ��
	uninitialized_fill_n(q, vi.size(), 42);
}