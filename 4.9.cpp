//sizeof

#include<iostream>
#include<string>
#include<vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

int main(void) {
	char ch = 'a';
	vector<int>b (5, 1);
	int p = 100;
	int& s = p;
	int* str = &p;
	cout << "char size is " << sizeof(ch) << endl;
	cout << "vector size is " << sizeof(b) << endl;
	b.push_back(234);
	cout << "after add,vector size is " << sizeof(b) << endl;
	cout << "s size is " << sizeof(s) << ",int size is " << sizeof(int) << endl;
	cout << "str size is " << sizeof(str) << endl;
	cout << "*str size is " << sizeof(*str) << endl;

	return 0;
}