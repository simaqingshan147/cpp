//IO类
//其余代码在笔记本上
#include<iostream>
using namespace std;

int main()
{
	cin.tie(&cout);        //标准库将cin和cout关联在一起
	ostream* old_tie = cin.tie(nullptr);     //cin不关联
	cin.tie(&cerr);                          //cin关联cerr
	cin.tie(old_tie);                        //重建cin与cout的关联

	return 0;
}