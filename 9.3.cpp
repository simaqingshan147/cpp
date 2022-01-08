//˳����������
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<forward_list>
using namespace std;

//string׷���ַ�
void knowledge1()
{
	string word;
	char c;
	while (cin >> c)
		word.push_back(c);

	cout << word << endl;
}


void knowledge2()
{
	//ͷ�巨
	list<int> ilist;
	for (size_t ix = 0; ix != 4; ++ix)
		ilist.push_front(ix);
}

void knowledge3()
{
	list<string> slist, v;
	v = { "quasi","simba","frollo","scar" };

	auto iter =--v.end();   //����v.end()-2
	iter--;

	//��v����λ���뵽slist��ͷ
	slist.insert(slist.begin(), iter, v.end());

	//����ɹ�,insert���ص�һ���¼���Ԫ�صĵ�����
	//����ʧ��,���ص�һ������
	string word;
	iter = slist.begin();
	//��ͷ����������
	//insert����ָ�����ĵ�һ��Ԫ�صĵ�����
	while (cin >> word)
		iter = slist.insert(iter, word);
}

//emplace
void knowledge4()
{
	class a {
	public:
		int c;
		int d;
		//���캯��
		a() = default;
		a(int v1, int v2) { c = v1; d = v2; }
	};

	vector<a> item;
	//emplace��Աʹ�ò���ֱ�ӹ���Ԫ��
	
	//item.emplace(1, 2);  ����
	//item.push_back(1, 2);  ����
	item.push_back(a(1, 2));   //������ʱ�������
	item.emplace_back();       //ʹ��a��Ĭ�Ϲ��캯��
	auto iter = item.begin();
	item.emplace(iter, 1, 2);   //ʹ��a�Ĺ��캯��,�ڿ�ͷ�����ʱ����
	item.emplace_back(1, 2);     //ָ��λ�ã��Զ�����
}

//����Ԫ��
void knowledge5()
{
	vector<int> vi(10, -2);    //10��-2
	auto a = *vi.begin();
	auto a2 = vi.front();   //��һ����������
	auto b = *(--vi.end());
	auto b2 = vi.back();   //���һ��Ԫ�ص�����,forward_list��֧��

	//ʹ��front��backҪȷ�������ǿ�


	//�ı�front��back
	int& c = vi.back();
	c = 12;
	int& d = vi.back();
	d = 14;

	//�����������
}

//ɾ��Ԫ��
void knowledge6()
{
	//pop_back,pop_front
	vector<int> ilist(10, 1);
	while (!ilist.empty())
	{
		cout << ilist.back() << endl;
		ilist.pop_back();
		//vectorû��pop_frontԪ��
	}
	//froward_list��֧��pop_back
	ilist = { 1,2,3,4,5,6,7,8 };
	auto it = ilist.begin();
	while (it != ilist.end())
	{
		if (*it % 2)
			it = ilist.erase(it);   //ɾ����Ԫ��,��ת����һԪ��
		//erase����ɾ��Ԫ�صĺ�һԪ�صĵ�����
		else
			++it;
	}
	//Ҫɾ���ĵ�һ��Ԫ��,Ҫɾ�������һ��Ԫ��֮���λ��
	//ɾ����it = ilist.end()
	it = ilist.erase(ilist.begin(), ilist.end());
	ilist.clear();  //ɾ������Ԫ��
}

//�����forward_list����
void knowledge7()
{
	//���룬ɾ��Ӱ��ǰ��
	//���������Ǵ�����ڵ�ǰ��
	forward_list<int> flst = { 0,1,2,3,4,5,6,7,8,9 };
	auto prev = flst.before_begin();  //ָ����Ԫ��֮ǰ�Ĳ�����Ԫ�أ���ͷ�ڵ�
	auto curr = flst.begin();         //��Ԫ��
	while (curr != flst.end())
	{
		if (*curr % 2)
			curr = flst.erase_after(prev);   //ɾ�����ƶ�curr
		else
		{
			prev = curr;
			++curr;  //ͬʱ��ǰ�ƶ�
		}
	}
}

//�ı�������С
void knowledge8()
{
	list<int> ilist(10, 42);  //10��42
	ilist.resize(15);        //��5��0��ӵ�ilist��ĩβ
	ilist.resize(25, -1);    //��10��-1��ӵ�ilistĩβ
	ilist.resize(5);         //ɾ����20��Ԫ��
}

//��д�ı�������ѭ������
void knowledge9()
{
	//ɾ��ż��Ԫ�أ���������Ԫ��
	vector<int> vi = { 0,1,2,3,4,5,6,7,8,9 };
	auto iter = vi.begin();

	//endһֱ�ڸ��£�Ӧ����ʱ���ã������Ǳ��������Ƚ�
	while (iter != vi.end())
	{
		if (*iter % 2)
		{
			iter = vi.insert(iter, *iter);
			iter += 2;  //iterָ�����Ԫ��,+2��������Ԫ�غ͸���Ԫ��
		}
		else
		{
			iter = vi.erase(iter);
			//iterָ��ɾ��Ԫ��֮���Ԫ��
		}
	}
}

int main()
{
	
	return 0;
}