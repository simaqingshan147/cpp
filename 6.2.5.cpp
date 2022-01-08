//main:处理命令行选项
#include<iostream>
using std::endl;
using std::cout;

//argc 数组中字符串数量
//argv 存储C风格字符串的数组
//aggv 第一个元素是程序名,最后一个指针之后的元素值尾0

int main(int argc, char* argv[])
{
	int i;
	for (i = 1; i < argc; i++)
		cout << *(argv[i]) << endl;

	return 0;
}

//6.2.5属性->调试->命令参数