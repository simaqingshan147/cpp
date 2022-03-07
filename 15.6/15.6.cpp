#include<15.h>

struct base{
    base():mem(0){}
    int memfcn(){return mem;}
protected:
    int mem;
};


//派生类成员将隐藏同名基类成员
struct derived:base
{
    //不能直接定义基类成员mem
    derived(int i):mem(i){}
    int get_mem(){return mem;}

    //使用作用域运算符来使用隐藏的基类成员
    int get_base_mem(){return base::mem;}

    //声明在内层作用域的函数不重载声明在外层作用域的函数
    //即使派生类成员与基类成员形参列表不一致，基类成员仍然隐藏
    int memfcn(int i){return i;}

protected:
    int mem;  //隐藏外层作用域(基类)名
};

//虚函数与作用域

class Base{
public:
    virtual int fcn();
};

//如果基类与派生类的虚函数实参不同
//则无法通过基类的引用和指针调用派生类虚函数
//因为派生类中虚函数会被隐藏而不是覆盖

class D1: public Base{
public:
    //fcn不覆盖虚函数，不是虚函数
    //fcn隐藏了Base的虚函数
    int fcn(int i){return i;}

    //假如需要覆盖Base::fcn，但不能删除fcn(i)
    //在Base有多个fcn的情况下，using让D1不用重新定义base的每个fcn
    //注意改变了base::fcn的访问权限为public
    using Base::fcn;
    int fcn(){return 30;}

    virtual void f2();  //新虚函数

};

class D2:public D1{
public:
    int fcn(int i){return 65535;}  //隐藏D1的fcn()
    int fcn(){return 20;}          //覆盖Base的虚函数
    void f2(){}                    //覆盖D1虚函数
};

int main(){

    //能使用什么成员由静态类型决定
    Bulk_quote bulk;
    Bulk_quote* p = &bulk;  //静态动态类型一致
    quote *p2 = &bulk;      //静态动态类型不一致
    p->discount_policy();    //可以访问
    //p2->discout_policy();    不能访问，哪怕动态类型是对的

    derived d(10);
    d.memfcn(10);
    //d.memfcn();  错误,memfcn被隐藏
    d.base::memfcn();

    Base bobj;
    D1 d1obj;
    D2 d2obj;
    Base *b1 = &bobj,*b2 = &d1obj,*b3= &d2obj;

    b1->fcn();   //调用Base::fcn
    b3->fcn();   //调用D2::fcn(),动态绑定
    //能使用那些成员由静态类型决定
    b2->fcn();   //调用Base::fcn,即使fcn在D1中隐藏,b2的静态类型是Base

    D1 *d1p = &d1obj;
    D2* d2p = &d2obj;

    //b2->f2();  错误,base中没有f2
    d1p->f2();   //调用D1::f2
    d2p->f2();   //调用D2::f2,动态绑定

    D1* d1tod2 = &d2obj;
    //错误,D1中fcn()被隐藏
    //在Base::fcn()被覆盖后正确，此时调用D1::fcn()
    d1tod2->fcn();
    d1tod2->fcn(42);   //D1::fcn(i)
    d1tod2->f2();      //D2::f2(),动态绑定
}