//标准库函数对象
#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;

int main(){
    plus<int> Intadd;  //执行int加法的函数对象
    int sum = Intadd(10,20);

    vector<string> s{"a","c","e","b"};
    //传入临时函数对象执行string的比较运算
    sort(s.begin(),s.end(),greater<string>());

    vector<string*> sp;

    //错误，直接比较指针，结果未定义
    sort(sp.begin(),sp.end(),
    [](string* a,string* b){return a<b;});

    //正确,标准库规定指针的less是定义良好的
    sort(sp.begin(),sp.end(),less<string*>());

    return 0;
}