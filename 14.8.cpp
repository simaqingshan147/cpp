//函数调用运算符
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct absInt{
    //重载函数调用运算符
    int operator()(int val) const{
        return val < 0 ? -1*val : val;
    }
};

class PrintString{
public:
        PrintString(ostream& o=cout,char c =' '):
        os(o),sep(c){}

        void operator()(const string& s){os<<s<<sep;}

private:
        ostream& os;  //写入流
        char sep;    //分隔符
};

int main(){
    int i = -42;
    absInt absObj;  //函数对象
    //"调用"函数对象
    int ui = absObj(i);

    //函数对象常做泛型算法的实参
    vector<string> s{"asdfkasd","adfasdf"};
    for_each(s.begin(),s.end(),PrintString(cerr,'\n'));

    return 0;
}

