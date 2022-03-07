#include<iostream>
#include"15.h"

class B{
public:
    B(){b=0;} //B()不被using继承,默认构造函数不继承
    B(int n){b=n;}

    //构造函数using不继承默认实参
    //下面一个函数using后会生成两个函数
    //D(m,n):B(m,n){}一个省略掉默认实参
    //D(m,n,t):B(m,n,t){}一个不省略
    B(int m,int n,int t=0){b = m;}
    B(const B& rhs) = delete;
    //无移动构造函数，也不会自动合成
protected:
    int b;
};

class D:public B{
public:
    int d;
    //未声明构造函数
    //没有移动构造函数，移动构造使用拷贝代替
};

class C:public B{
public:
    int c;
private:
    //使用using直接重用基类构造函数
    //对于构造函数，using命令编译器为基类每一个构造函数生成代码
    // C(n):B(n){}派生类数据c默认初始化,b=n

    using B::B;  //构造函数的using声明不改变访问级别
    //C(int a,int b,int d){c=d;}

    //没有显式定义构造函数
};

int main(){
    quote* p = new quote;
    quote* p2 = new Bulk_quote;
    
    delete p;   //quote的析构函数
    delete p2;  //bulk_quote的析构函数

    D d;  //D的合成默认构造函数使用B的默认构造函数
    //D d2(d);  D的合成拷贝构造函数是删除
    //D d3(std::move(d));  隐式使用D的删除拷贝构造函数

    C cp;      //合成默认构造函数,而不是using继承B()

    //使用using生成的C(n):B(n){}
    C c(2);     //生成的构造函数还是B:B(n)的public级别

    C c2(2,3);  //默认实参省略掉的版本
    C c3(2,3,4); //默认实参未省略的版本

    //在C的private加上C(a,b,d)后,c2.c3不能构造
    //因为using不继承与派生类构造函数参数列表相同的函数
    //所以c2,c3使用的继承B(m,n,t)的生成构造函数不可用


    return 0;
}