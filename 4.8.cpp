#include <iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;

int main(void) {
	unsigned long quizl = 0;
	quizl |= 1UL << 27;  //������27λΪ1������λΪ0
	cout << quizl << endl;
	quizl &= ~(1UL << 27);
	cout << quizl << endl;
	return 0;
}
