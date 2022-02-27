//类型转换运算符
//面向任意能作为函数返回类型的类型,除了void
//即不能转到void,数组，函数类型
//无显式返回类型，无形参,必须是成员函数，一般为const
#include<iostream>
using namespace std;

class smallInt{
    friend smallInt operator+(const smallInt&,const smallInt&);
    public:
    smallInt(int i=0):val(i)
    {
        if(i<0||i>255)
            throw out_of_range("Bad smallInt value!");
    }
    //显式转换，不允许隐式转换
    explicit operator int() const{return val;}
    private:
    size_t val;
};

smallInt operator+(const smallInt& i,const smallInt& j){
    return i.val+j.val;
}

int main(){
    smallInt si;
    si = 4;  //4隐式转换为smallInt,然后调用=
    //si+3;  错误，si是隐式转换为int

    //内置类型转换将double转换为int
    smallInt s2 = 3.14;
    //用户定义转换和标准内置类型转换
    //s2 + 3.14;

    static_cast<int>(si) + 3;  //正确，显式转换

    smallInt s3 = si + s2;  //+调用友元函数

    //假如int()不是显式的，则这里会有二义性
    //是内置+还是友元+
    //int i = s3 + 0;

    return 0;
}