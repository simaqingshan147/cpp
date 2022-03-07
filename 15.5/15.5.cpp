#include<iostream>
#include<string>
using namespace std;

class base{
public:
    friend class pal;  //基类的友元类
    int pub_mem(){};
protected:
    int prot_mem;
private:
    char priv_mem;
};

//派生类的成员和友元只能通过派生类对象访问基类的受保护成员
//派生类对基类对象中的受保护成员没有访问权
class sneaky: public base{
    friend void clobber(sneaky&);  //能访问sneaky::prot_mem
    friend void clobber(base&);    //不能访问base::prot_mem
    int j;
    //char g(){return priv_mem;} 派生类不可访问private成员
};

//派生类访问说明符控制派生类用户和派生类的派生类对基类成员的访问权限
//private让基类成员成了该类的private成员
struct priv_derv:private base{
//private不影响派生类访问权限
//对基类成员的访问权限只与基类中的访问说明符有关
int f1()const{return prot_mem;}  //仍然是protected的
};

struct derived_from_private:public priv_derv{
    //base::prot_mem在priv_derv中是private的
    //int use_base(){return prot_mem;} 错误
};

//友元能访问private和protected对象
void clobber(sneaky&s){s.j=s.prot_mem=0;}
//友元不能基类受保护对象
//void clobber(base &b){b.prot_mem = 0;}

//基类友元不能访问派生类成员
//派生类友元不能访问基类成员
class pal{
public:
    int f(base b){return b.prot_mem;} //正确
    //int f2(sneaky s){return s.j;}  错误,友元不具继承性，不能访问派生类成员
    int f3(sneaky s){return s.prot_mem;}  //正确,prot_mem是base成员  
};

class base2{
public:
    size_t size() const{return n;}
protected:
    size_t n;
private:
    int pri;
};

//base2成员为private
class derived: private base2{
public:
    //使用using声明改变可访问对象的访问权限
    using base2::size;  //维持size的public访问级别
protected:
    using base2::n;
    //using base2::pri; 错误,只能改变派生类可访问对象的权限
};

//struct和class唯一差别就是默认成员访问说明符及默认派生类访问说明符
struct D1:base2{};   //默认public继承
class D2:base2{};    //默认private继承

int main(){
    sneaky d1;
    priv_derv d2;

    d1.pub_mem();
    //d2.pub_mem();  基类成员在该派生类private
}