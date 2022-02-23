//13.6.1 ---- 右值引用
#include<iostream>
#include<utility>  //move
using namespace std;
int main() {
    int &&rr = 42;  //右值引用，绑定到字面常量
    int i = 42;
    //int &&r = i; 
    const int &r3 = i*42;  //将const引用绑定到右值
    int &&rr5 = i*42;  //右值绑定到乘法结果上
    //后置运算符返回临时值i,是不能修改的右值
    int &&rr3 = i--;  //后置运算符返回右值

    int &&rr1 = 42;
    ;//int &&rr2 = rr1;  rr1是变量(左值)

    //move函数
    //将左值rr1转化为对应的右值引用
    int &&rr4 = std::move(rr1);
    cout<<"rr1= "<<rr1<<endl;
    cout<<"rr4= "<<rr4<<endl;
    rr1 = 50;
    cout<<"rr1= "<<rr1<<endl;
    cout<<"rr4= "<<rr4<<endl;
    rr4 = 60;
    cout<<"rr1= "<<rr1<<endl;
    cout<<"rr4= "<<rr4<<endl;
    return 0;
}