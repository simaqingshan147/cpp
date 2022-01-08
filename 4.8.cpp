#include <iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;

int main(void) {
	unsigned long quizl = 0;
	quizl |= 1UL << 27;  //该数是27位为1，其他位为0
	cout << quizl << endl;
	quizl &= ~(1UL << 27);
	cout << quizl << endl;
	return 0;
}
